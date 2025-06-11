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
Construa o circuito conforme abaixo (ver Ligações do Circuito)
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

