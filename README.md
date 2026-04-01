# 📦 Caixa Acessível

## 📖 Sobre o Projeto

A **Caixa Acessível** é uma solução tecnológica desenvolvida com o objetivo de promover **acessibilidade, autonomia e inclusão** no ambiente educacional, especialmente para alunos surdos.

O projeto surgiu a partir da necessidade de melhorar a comunicação entre professor e aluno surdo em sala de aula, evitando interrupções invasivas e proporcionando uma experiência de aprendizado mais fluida e confortável.

A solução consiste em uma **caixa equipada com um LED de baixa intensidade**, controlada remotamente pelo professor através de uma interface web. Quando acionada, a caixa emite um sinal luminoso discreto para chamar a atenção do aluno.

---

## 🎯 Objetivo

- Promover inclusão no ambiente educacional  
- Melhorar a comunicação entre professor e aluno surdo  
- Evitar abordagens invasivas (como toque físico)  
- Oferecer uma solução simples, eficaz e replicável  

---

## 💡 Contexto

A educação inclusiva é um dos pilares fundamentais de uma sociedade mais justa e igualitária. No entanto, desafios como limitações estruturais e pedagógicas ainda dificultam a plena integração de alunos com necessidades específicas.

Durante a experiência com um aluno surdo oralizado em um curso de Programador Full Stack, foram identificados problemas como:

- Divisão de atenção entre intérprete e conteúdo  
- Dificuldade de comunicação direta durante a aula  
- Interrupções que causavam desconforto  

A partir dessas observações, o projeto foi desenvolvido em três etapas:

1. **Reorganização do ambiente**  
   Posicionamento do intérprete próximo ao professor

2. **Identificação de novos desafios**  
   Dificuldade em chamar a atenção do aluno sem contato físico

3. **Desenvolvimento da solução**  
   Criação da caixa com LED acionada remotamente

---

## 🛠️ Tecnologias Utilizadas

### Hardware

- ESP32  
- LED de baixa intensidade  
- Estrutura impressa em 3D  

### Software

- HTML  
- CSS  
- JavaScript  
- Python (servidor)  

---

## ⚙️ Funcionamento

1. O professor acessa uma interface web  
2. Ao acionar um comando, o servidor envia um sinal  
3. O ESP32 recebe o sinal via rede  
4. O LED da caixa é ativado  
5. O aluno percebe o sinal visual de forma discreta  

---

## 🧩 Arquitetura do Sistema


[ Interface Web ]
↓
[ Servidor Python ]
↓
[ ESP32 ]
↓
[ LED (Caixa Acessível) ]


---

## 🚀 Como Executar

### Pré-requisitos

- Python instalado  
- ESP32 configurado  
- Conexão de rede entre servidor e dispositivo  

### Passos

1. Clone o repositório:

```bash
git clone https://github.com/jpmoraes/OI_CaixaAcessivel.git
```

2. Acesse a pasta do projeto:
```
cd OI_CaixaAcessivel
```

3. Execute o servidor:

```
python app.py
```

4. Abra a interface web no navegador

5. Conecte o ESP32 à mesma rede
