#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <ESPmDNS.h>
#include <DNSServer.h>

#define LED_CAIXA 18

const char* apSSID = "Caixa-Oi-ESP32";
const char* apPassword = "12345678"; // Altere antes de usar em ambiente publico
const char* nomeLocal = "caixaoi";
IPAddress apIP(192, 168, 100, 1);
IPAddress apGateway(192, 168, 100, 1);
IPAddress apMask(255, 255, 255, 0);

WebServer server(80);
DNSServer dnsServer;
Preferences preferences;
String wifiSSID, wifiPassword;
bool mdnsAtivo = false;
unsigned long ultimaVerificacao = 0;

String escaparHTML(String valor) {
  valor.replace("&", "&amp;");
  valor.replace("<", "&lt;");
  valor.replace(">", "&gt;");
  valor.replace("\"", "&quot;");
  valor.replace("'", "&#39;");
  return valor;
}


void carregarWiFi() {
  preferences.begin("wifi", true);
  wifiSSID = preferences.getString("ssid", "");
  wifiPassword = preferences.getString("pass", "");
  preferences.end();
}

void salvarWiFi(const String& ssid, const String& senha) {
  preferences.begin("wifi", false);
  preferences.putString("ssid", ssid);
  preferences.putString("pass", senha);
  preferences.end();
}

bool conectarWiFi(const String& ssid, const String& senha) {
  if (ssid.isEmpty()) return false;
  // Mantem o ponto de acesso ativo enquanto conecta ao roteador.
  if (mdnsAtivo) { MDNS.end(); mdnsAtivo = false; }
  WiFi.disconnect(false, false);
  delay(150);
  WiFi.begin(ssid.c_str(), senha.c_str());
  Serial.print("Conectando a ");
  Serial.println(ssid);
  for (int i = 0; i < 30 && WiFi.status() != WL_CONNECTED; ++i) {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("IP da rede: ");
    Serial.println(WiFi.localIP());
    return true;
  }
  Serial.println("Nao foi possivel conectar. AP continua disponivel.");
  return false;
}

void iniciarMDNS() {
  if (mdnsAtivo || WiFi.status() != WL_CONNECTED) return;
  if (MDNS.begin(nomeLocal)) {
    MDNS.addService("http", "tcp", 80);
    mdnsAtivo = true;
    Serial.println("Acesso local: http://caixaoi.local");
  } else {
    Serial.println("mDNS indisponivel; use o IP mostrado na pagina do AP.");
  }
}

String cabecalho(const String& titulo) {
  return String("<!DOCTYPE html><html lang='pt-br'><head><meta charset='utf-8'>") +
    "<meta name='viewport' content='width=device-width, initial-scale=1'>" +
    "<title>" + titulo + "</title><style>" +
    "body{font-family:Arial,sans-serif;background:#101820;color:white;text-align:center;margin:0;padding:20px}" +
    ".box{max-width:430px;margin:30px auto;background:#1f2937;padding:25px;border-radius:18px;box-sizing:border-box}" +
    "h1{color:#00e5ff}a{color:#67e8f9;overflow-wrap:anywhere}" +
    ".btn,button{display:block;box-sizing:border-box;width:100%;padding:14px;margin:12px 0;border:0;border-radius:12px;background:#2563eb;color:white;text-decoration:none;font-size:17px;cursor:pointer}" +
    ".verde{background:#16a34a}.vermelho{background:#dc2626}" +
    "input{box-sizing:border-box;width:100%;padding:12px;margin:8px 0;border-radius:8px;border:0}" +
    ".info{background:#111827;padding:15px;border-radius:10px;line-height:1.7;overflow-wrap:anywhere}" +
    "</style></head><body><div class='box'>";
}

String rodape() { return "</div></body></html>"; }

String paginaHome() {
  String html = cabecalho("Caixa Oi");
  html += "<h1>CAIXA OI</h1><p>ESP32 WROOM</p>";
  html += "<a class='btn' href='/wifi'>Configurar Wi-Fi</a>";
  html += "<a class='btn verde' href='/caixa'>Acionar Caixa Oi</a>";
  html += "<a class='btn' href='/ip'>Consultar IP</a>";
  html += "<div class='info'>";
  if (WiFi.status() == WL_CONNECTED) {
    html += "Wi-Fi conectado: " + escaparHTML(wifiSSID) + "<br>IP: <strong>" + WiFi.localIP().toString() + "</strong>";
    html += "<br>Caminho Alternativo: <a href='http://caixaoi.local/'>caixaoi.local</a>";
  } else {
    html += "Sem conexao com roteador. Configure o Wi-Fi.";
  }
  html += "<br>Rede de recuperacao: " + String(apSSID) + "<br>IP para recuperar: " + WiFi.softAPIP().toString();
  html += "</div>" + rodape();
  return html;
}

String paginaWiFi() {
  String html = cabecalho("Configurar Wi-Fi");
  html += "<h2>Configurar Wi-Fi</h2>";
  html += "<form action='/salvarwifi' method='POST'>";
  html += "<input name='ssid' maxlength='32' required placeholder='Nome da rede Wi-Fi'>";
  html += "<input name='senha' type='password' maxlength='63' placeholder='Senha do Wi-Fi'>";
  html += "<button class='verde' type='submit'>Conectar</button></form>";
  html += "<a href='/'>Voltar</a>" + rodape();
  return html;
}

String paginaCaixa() {
  String html = cabecalho("Controle Caixa Oi");
  html += "<h1>CAIXA OI</h1><h2>Status: ";
  html += digitalRead(LED_CAIXA) == HIGH ? "LIGADA" : "DESLIGADA";
  html += "</h2><a class='btn verde' href='/ligar'>LIGAR</a>";
  html += "<a class='btn vermelho' href='/desligar'>DESLIGAR</a>";
  html += "<a href='/'>Voltar</a>" + rodape();
  return html;
}

String paginaIP() {
  String html = cabecalho("Consultar IP");
  html += "<h1>Enderecos da Caixa Oi</h1><div class='info'>";
  if (WiFi.status() == WL_CONNECTED) {
    String url = "http://" + WiFi.localIP().toString() + "/";
    html += "IP atual: <strong>" + WiFi.localIP().toString() + "</strong>";
    html += "<br><a href='" + url + "'>Abrir Caixa Oi no Wi-Fi</a>";
    html += "<br>Nome local: <a href='http://caixaoi.local/'>caixaoi.local</a>";
  } else {
    html += "ESP32 ainda nao conectado ao roteador.";
  }
  html += "<br>AP: " + String(apSSID) + "<br>Endereco do AP: " + WiFi.softAPIP().toString();
  html += "</div><p>Para usar o IP da rede, conecte seu celular/computador ao mesmo Wi-Fi do ESP32.</p>";
  html += "<a href='/'>Voltar</a>" + rodape();
  return html;
}

void configurarServidor() {
  server.on("/", HTTP_GET, []() { server.send(200, "text/html; charset=utf-8", paginaHome()); });
  server.on("/wifi", HTTP_GET, []() { server.send(200, "text/html; charset=utf-8", paginaWiFi()); });
  server.on("/ip", HTTP_GET, []() { server.send(200, "text/html; charset=utf-8", paginaIP()); });
  server.on("/caixa", HTTP_GET, []() { server.send(200, "text/html; charset=utf-8", paginaCaixa()); });
  server.on("/ligar", HTTP_GET, []() {
    digitalWrite(LED_CAIXA, HIGH);
    server.sendHeader("Location", "/caixa", true);
    server.send(303, "text/plain", "");
  });
  server.on("/desligar", HTTP_GET, []() {
    digitalWrite(LED_CAIXA, LOW);
    server.sendHeader("Location", "/caixa", true);
    server.send(303, "text/plain", "");
  });
  server.on("/salvarwifi", HTTP_POST, []() {
    String novoSSID = server.arg("ssid");
    String novaSenha = server.arg("senha");
    novoSSID.trim();
    if (novoSSID.isEmpty()) {
      server.send(400, "text/plain; charset=utf-8", "Informe o nome da rede.");
      return;
    }
    // Mantem o AP ativo enquanto tenta entrar na rede do roteador.
    bool sucesso = conectarWiFi(novoSSID, novaSenha);
    if (sucesso) {
      wifiSSID = novoSSID;
      wifiPassword = novaSenha;
      salvarWiFi(wifiSSID, wifiPassword);
      iniciarMDNS();
      String html = cabecalho("Wi-Fi conectado");
      html += "<h2>Wi-Fi conectado!</h2><p>Novo IP: <strong>" + WiFi.localIP().toString() + "</strong></p>";
      html += "<p>Conecte seu celular/computador ao Wi-Fi <strong>" + escaparHTML(wifiSSID) + "</strong>.</p>";
      html += "<div class='info'><strong>Proximo passo:</strong><br>1. Desconecte-se da rede Caixa-Oi-ESP32.<br>2. Conecte este dispositivo a mesma rede Wi-Fi configurada: <strong>" + escaparHTML(wifiSSID) + "</strong>.<br>3. Abra no navegador o endereco IP mostrado acima.</div>";
      html += "<p>Quando estiver na mesma rede, digite o IP acima no navegador.</p>";
      html += "<p>Ou acesse <strong>http://caixaoi.local</strong> (se sua rede suportar mDNS).</p>";
      html += rodape();
      server.send(200, "text/html; charset=utf-8", html);
    } else {
      String html = cabecalho("Falha na conexao");
      html += "<h2>Nao foi possivel conectar</h2><p>Confira a rede e a senha.</p>";
      html += "<a class='btn' href='/wifi'>Tentar novamente</a>" + rodape();
      server.send(200, "text/html; charset=utf-8", html);
    }
  });
  server.onNotFound([]() {
    // Ajuda na abertura do portal quando conectado diretamente ao AP.
    if (server.hostHeader() != WiFi.softAPIP().toString() && WiFi.status() != WL_CONNECTED) {
      server.sendHeader("Location", "http://192.168.100.1/", true);
      server.send(302, "text/plain", "");
    } else {
      server.send(404, "text/plain", "Pagina nao encontrada");
    }
  });
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_CAIXA, OUTPUT);
  digitalWrite(LED_CAIXA, LOW);
  WiFi.persistent(false);
  WiFi.setAutoReconnect(true);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apGateway, apMask);
  if (!WiFi.softAP(apSSID, apPassword)) Serial.println("Falha ao criar AP");
  Serial.print("IP fixo do AP: ");
  Serial.println(WiFi.softAPIP());
  dnsServer.start(53, "*", WiFi.softAPIP());
  carregarWiFi();
  if (!wifiSSID.isEmpty()) {
    if (conectarWiFi(wifiSSID, wifiPassword)) iniciarMDNS();
  }
  configurarServidor();
  server.begin();
  Serial.println("Servidor Caixa Oi iniciado.");
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
  // Em caso de queda da rede, a interface STA tenta se reconectar.
  // O endereco caixaoi.local e republicado apos a reconexao.
  if (millis() - ultimaVerificacao >= 5000) {
    ultimaVerificacao = millis();
    if (WiFi.status() == WL_CONNECTED) {
      iniciarMDNS();
    } else {
      if (mdnsAtivo) { MDNS.end(); mdnsAtivo = false; }
      if (!wifiSSID.isEmpty()) WiFi.reconnect();
    }
  }
}
