Lâmpada de Lava Interativa com LEDs RGB Endereçáveis e Sensor de Distância
Este projeto simula uma lâmpada de lava digital: um sensor ultrassônico detecta a distância de um objeto, e os LEDs mudam de cor e intensidade com base nessa informação.


## Table of Contents
1. About
2. RoadMap
3. Getting Started
   3.1 Prerequisites
   3.2. Installation
   3.3 Usage
4. Contributing
5. Code of Conduct
6. License
7. Credits
8. Contributors

---

## 1. About
Este projeto foi desenvolvido para criar uma experiência visual interativa através de uma fita de LED controlada por um sensor de distância ultrassônico. Ele simula uma lâmpada de lava moderna, onde a cor e intensidade da luz mudam de acordo com a distância de um objeto.

---

## 2. RoadMap
- Definir Projeto: Criação de uma lâmpada de lava digital interativa com sensores e LEDs.

- Construção do Circuito: Prototipagem do sistema com Arduino, HC-SR04 e WS2812B.

- Testes e Ajustes: Mapeamento da distância e efeitos de luz dinâmicos.

- Documentação: Produção do README e esquemas.

---

## 3. Getting Started
# 3.1 Prerequisites
- Arduino IDE: v2.2.1 ou superior

- Biblioteca Adafruit NeoPixel: v1.11.0
Instale via Arduino IDE → Ferramentas → Gerenciar Bibliotecas


- Lista de Materiais
Quantidade      Item
1x	            Placa Arduino Uno
1x	            Sensor Ultrassônico HC-SR04
1x	            Fita de LED WS2812B (30 LEDs)
1x	            Fonte de alimentação 5V 2A
Vários	        Cabos Jumper
1x	            Protoboard


# 3.2 Installation
Construa o circuito conforme presente no repositório
Instale a biblioteca Adafruit NeoPixel v1.11.0
Copie o código-fonte para o Arduino IDE
Compile e faça o upload para o Arduino Uno
Abra o Monitor Serial para visualizar a leitura da distância


# 3.3 Usage
- Ligações do Circuito

- Sensor Ultrassônico HC-SR04
HC-SR04     Arduino
VCC         5V
GND	        GND
Trig	    8
Echo	    7

- Fita de LED WS2812B
LED         Arduino
DIN	        6
VCC	        5V (via fonte externa)
GND	        GND

> A fonte externa de 5V precisa fornecer pelo menos 2A. O GND da fonte deve estar ligado ao GND do Arduino.

- Como Funciona
    - Inicialização
        Define os pinos e inicia a comunicação Serial
    - Leitura do Sensor
        Mede distância via pulso de ultrassom

    - Processamento de Dados
        Distância entre 25cm e 200cm afeta LEDs
        Cor calculada em HSV → convertida para RGB

    - Saída Visual
        Mais perto: mais LEDs + mistura de cor
        Mais longe: menos LEDs + cor pura

- Environment Variables
    Este projeto não utiliza variáveis de ambiente. Porém, o código pode ser adaptado para aceitar parâmetros externos futuramente.

    Código de Exemplo:

digitalWrite(trigPin, LOW);
delayMicroseconds(3);
digitalWrite(trigPin, HIGH);
delayMicroseconds(12);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance = (duration * 0.034) / 2;

int activeLEDs = map(distance, 200, 25, 0, numPixels);
int mixAmount = map(distance, 200, 25, 0, 255);

---

## 4. Contributing
Contribuições são bem-vindas! Para colaborar:
Faça um fork do repositório
Crie uma branch (git checkout -b feature/NovaFuncionalidade)
Commit suas mudanças (git commit -m 'Adiciona nova funcionalidade')
Push para a branch (git push origin feature/NovaFuncionalidade)
Abra um Pull Request

---

## 5. Code of Conduct
Todos os participantes devem seguir o Código de Conduta do projeto. Comportamentos respeitosos e inclusivos são esperados.

---

## 6. License
Este projeto está licenciado sob a licença MIT.

---

## 7.Credits
- Desenvolvido no âmbito da unidade curricular do Mestrado em Design e Multimédia da Universidade de Coimbra

- Biblioteca: Adafruit NeoPixel

- Inspiração: Lâmpadas de lava clássicas e arte interativa com LEDs


---
## 8. Contributors
Carolina Travanca, Clara Gomes, Flávia Simões - MDM


Leitor de Cassetes Interativo com NFC + MQTT + Processing
Este projeto simula um leitor de cassetes interativo utilizando ESP32 e leitor NFC. As “cassetes” são representadas por tags NFC, que ao serem lidas, disparam a reprodução de músicas específicas e visualizações gráficas no Processing, através de mensagens MQTT.


## TABLE OF CONTENTS
1. About
2. RoadMap
3. Getting Started
   3.1. Prerequisites
   3.2. Installation
   3.3. Usage
4. Contributing
5. Code of Conduct
6. License
7. Credits
8. Contributors


## 1. ABOUT
Este projeto une eletrónica, redes e arte generativa: um ESP32 lê tags NFC, publica mensagens via MQTT, e um sketch em Processing reage às mensagens, tocando músicas diferentes com visualizações.

Inspirado na nostalgia das cassetes analógicas, mas com tecnologia moderna.

---

## 2. ROADMAP
Definição da Arquitetura: ESP32 + MFRC522 + MQTT + Processing
Configuração do Hardware e Rede
Desenvolvimento do Código ESP32
Criação do Sketch no Processing
Testes de Integração e UX
Documentação e Organização do Projeto

---

## 3. Getting Started
# 3.1 Prerequisites
- Hardware
   ESP32 DevKit
   Leitor NFC MFRC522
   2 ou mais tags NFC com UIDs únicos
   Botão físico
   Jumpers, protoboard
   Acesso à rede WiFi

- Software
   Arduino IDE (com suporte ESP32)
   Processing IDE
   MQTT Broker (ex: HiveMQ público)

- Bibliotecas Arduino
   MFRC522
   WiFi (nativa no ESP32)
   PubSubClient

- Bibliotecas Processing
   MQTT
   Sound

---

# 3.2. Installation
# Parte 1 — ESP32
- Instale as bibliotecas no Arduino IDE:
   MFRC522
   PubSubClient

- Faça o upload do código para o ESP32.

- Substitua as credenciais WiFi no código (SSID e password).

- Abra o Monitor Serial e aproxime tags NFC para testar os UIDs e publicações MQTT.

# Parte 2 — Processing
- Crie uma pasta (ex: LeitorCasseteProcessing/) com:

LeitorCasseteProcessing/
├── leitor_processing.pde
├── toxic.mp3
├── babe.mp3

- Instale as bibliotecas via Sketch > Import Library > Add Library...:
   Sound
   MQTT

- No código .pde, edite os UIDs reais das suas tags:
   String n = "4EB79AD6A2681";
   String n2 = "4C279AD6A2681";

---

# 3.3 Usage
- Conecte os componentes conforme abaixo:

Conexões MFRC522 com ESP32
MFRC522	   ESP32
SDA	      GPIO 4
SCK	      GPIO 18
MOSI	      GPIO 23
MISO	      GPIO 19
RST	      GPIO 13
GND	      GND
3.3V	      3.3V

## Nunca conecte o MFRC522 ao 5V
Conexão do Botão
Um pino: GPIO 14
Outro: GND

# Teste Completo
Construa o circuito conforme presente no repositório
Execute o sketch no Processing
Ligue o ESP32 e abra o Monitor Serial
Aproxime uma tag NFC → toca uma música específica e inicia visualização
Troque de tag → muda a música
Pressione o botão → a música para

# Ambiente e Segurança
Este projeto não usa variáveis de ambiente, mas contém dados sensíveis como:
SSID/senha WiFi
Códigos UID de tags

Não publique esses dados em repositórios públicos

# Dicas de Depuração
Verifique arquivos .mp3 na pasta correta
Confira SSID e senha WiFi
Use println(code) no Processing para ver se o UID está sendo recebido
Use ferramentas como MQTT Explorer para monitorar tópicos e mensagens

# Broker MQTT
Broker: broker.hivemq.com
Porta: 1883
Tópico: leitor

---

## 4. Contributing
Contribuições são bem-vindas!

Fork o repositório
Crie sua branch (git checkout -b minha-funcionalidade)
Commit suas mudanças (git commit -m "feat: nova função")
Push para o seu fork (git push origin minha-funcionalidade)
Abra um Pull Request

---

## 5. Code of Conduct
Todos os participantes deste projeto devem seguir nosso Código de Conduta.

---

## 6. License
Este projeto está licenciado sob a licença MIT.

---

## 7. Credits
Desenvolvido no contexto do Mestrado em Design e Multimédia da Universidade de Coimbra
Biblioteca MFRC522 por Miguel Balboa
Biblioteca PubSubClient por Nick O’Leary
Broker público: HiveMQ
Bibliotecas Processing: Sound, MQTT (StudioSAVSoft)

---

## 8. Contributors
Carolina Travanca, Clara Gomes, Flávia Simões - MDM
