📦 Caixa Acessível

📖 Sobre o Projeto

A Caixa Acessível é uma solução tecnológica desenvolvida com o objetivo de promover acessibilidade, autonomia e inclusão no ambiente educacional, especialmente para alunos surdos. O projeto surgiu a partir da necessidade de melhorar a comunicação entre professor e aluno surdo em sala de aula, evitando interrupções invasivas e proporcionando uma experiência de aprendizado mais fluida e confortável. A solução consiste em uma caixa equipada com um LED de baixa intensidade, controlada remotamente pelo professor através de uma interface web. Quando acionada, a caixa emite um sinal luminoso discreto para chamar a atenção do aluno.

🎯 Objetivo
Promover inclusão no ambiente educacional
Melhorar a comunicação entre professor e aluno surdo
Evitar abordagens invasivas (como toque físico)
Oferecer uma solução simples, eficaz e replicável

💡 Contexto

A educação inclusiva é um dos pilares fundamentais de uma sociedade mais justa e igualitária. No entanto, desafios como limitações estruturais e pedagógicas ainda dificultam a plena integração de alunos com necessidades específicas. Durante a experiência com um aluno surdo oralizado em um curso de Programador Full Stack, foram identificados problemas como:
Divisão de atenção entre intérprete e conteúdo
Dificuldade de comunicação direta durante a aula
Interrupções que causavam desconforto

A partir dessas observações, o projeto foi desenvolvido em três etapas:

Reorganização do ambiente
Posicionamento do intérprete próximo ao professor
Identificação de novos desafios
Dificuldade em chamar a atenção do aluno sem contato físico
Desenvolvimento da solução
Criação da caixa com LED acionada remotamente

🛠️ Tecnologias Utilizadas

Hardware
ESP32
LED de baixa intensidade
Estrutura impressa em 3D
Software
HTML
CSS
JavaScript
Python (servidor)

⚙️ Funcionamento

O professor acessa uma interface web
Ao acionar um comando, o servidor envia um sinal
O ESP32 recebe o sinal via rede
O LED da caixa é ativado
O aluno percebe o sinal visual de forma discreta

🧩 Arquitetura do Sistema

[ Interface Web ]
        ↓
[ Servidor Python ]
        ↓
[ ESP32 ]
        ↓
[ LED (Caixa Acessível) ]

🚀 Como Executar

Pré-requisitos
Python instalado
ESP32 configurado
Conexão de rede entre servidor e dispositivo
Passos
Clone o repositório:
git clone https://github.com/jpmoraes/OI_CaixaAcessivel.git
Acesse a pasta do projeto:
cd OI_CaixaAcessivel
Execute o servidor:
python app.py
Abra a interface web no navegador
Conecte o ESP32 à mesma rede

📊 Resultados

Melhora significativa na comunicação em sala
Redução de situações constrangedoras
Maior autonomia para o aluno
Reação positiva e emocional da turma

🌍 Impacto

A solução demonstrou que pequenas inovações podem gerar grandes impactos na educação inclusiva. O projeto pode ser adaptado e replicado em diferentes contextos educacionais, ampliando seu alcance.

🔄 Expansão

O projeto foi integrado a uma iniciativa maior, incluindo o desenvolvimento de um site de programação voltado para a comunidade surda, reforçando o compromisso com acessibilidade digital.

🤝 Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para:

Abrir issues
Sugerir melhorias
Criar pull requests

📜 Licença

Este projeto está disponível para uso educacional e pode ser adaptado conforme necessário.
