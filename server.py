import os
import requests
from http.server import BaseHTTPRequestHandler, HTTPServer

# IP do ESP32 para o qual a requisição GET será enviada
ESP32_IP = "172.26.3.80"  # Substitua pelo IP real do ESP32

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Serve a página index.html
        if self.path == '/':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            if os.path.exists('index.html'):
                with open('index.html', 'r') as file:
                    self.wfile.write(file.read().encode())
            else:
                self.send_response(404)
                self.end_headers()
                self.wfile.write(b'index.html not found')

        # Serve o arquivo CSS (no diretório css)
        elif self.path.startswith('/css/'):
            self.serve_static_file(self.path, 'css')
        
        # Serve o arquivo JavaScript (no diretório js)
        elif self.path.startswith('/js/'):
            self.serve_static_file(self.path, 'js')
        
        # Ações do ESP32
        elif self.path == '/turn_on':
            self.send_esp32_request('turn_on')
        elif self.path == '/turn_off':
            self.send_esp32_request('turn_off')
        
        # Caso não seja encontrado
        else:
            self.send_response(404)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            self.wfile.write(b'Not Found')

    def serve_static_file(self, path, folder):
        """ Serve arquivos estáticos (CSS, JS, etc.). """
        file_path = path.lstrip(f'/{folder}/')  # Remove a parte /css/ ou /js/
        full_path = os.path.join(folder, file_path)

        if os.path.exists(full_path):
            # Determinar o tipo MIME (Conteúdo)
            if full_path.endswith('.css'):
                content_type = 'text/css'
            elif full_path.endswith('.js'):
                content_type = 'application/javascript'
            else:
                content_type = 'application/octet-stream'

            self.send_response(200)
            self.send_header('Content-type', content_type)
            self.end_headers()

            with open(full_path, 'rb') as file:
                self.wfile.write(file.read())
        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(b'File not found')

    def send_esp32_request(self, action):
        """ Envia a requisição GET para o ESP32 e trata o retorno. """
        try:
            response = requests.get(f'http://{ESP32_IP}/{action}')
            message = response.text
            status_code = response.status_code
        except requests.RequestException as e:
            message = f'Error: {str(e)}'
            status_code = 500

        self.send_response(status_code)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd server on port {port}...')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nServer stopped by user.")
        httpd.server_close()

if __name__ == '__main__':
    run()
