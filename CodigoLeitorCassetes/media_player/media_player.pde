import processing.sound.*;
import processing.serial.*;
import mqtt.*;

SoundFile M1, M2;
Serial myPort;
MQTTClient client;
String ID = "";
String letters = "abcdefghijklmnopqrstuvwxyz0123456789";
String n = "4EB79AD6A2681"; //codigos tags
String n2 = "4C279AD6A2681";
String stop = "STOP"; //parar o audio (mensagem enviada para o cliente)
//boolean aTocar = false; //comeca sem nenhum audio

// variaveis que analisam o som recebido a varios niveis
AudioIn input;
Amplitude amp;
FFT fft;
Waveform waveform;

// variaveis para visualizacao dos dados recebidos por audio
int bands = 128;         // frequencia de FFT
float[] spectrum = new float[bands];
float smoothingFactor = 0.2;  //  transicao mais suave de frequencias
float[] waveformData = new float[512];  // data waveform
float[] lastSpectrum = new float[bands]; //ultimo espectro analisado

color[] colorPalette = { //cores que irao aparecer nas barras, mudam conforme os parametros
  color(0,0,255),   
  color(100, 13, 200),   
  color(105, 120, 5),    
  color(200, 10, 10),    
  color(115, 0, 205)    
};

void setup() {
   fullScreen();
 
  background(0);
  
  M1 = new SoundFile(this, "toxic.mp3"); //musicas incluidas em cada uma das cassetes
  M2 = new SoundFile(this, "babe.mp3");
  
  //  comeco da analise FFT
  fft = new FFT(this, bands);
  amp = new Amplitude(this);
  waveform = new Waveform(this, 512);
  
 
 //criacao de id para acesso ao MQTT
  for (int i = 0; i < 10; i++) {
    ID = ID + letters.charAt(int(random(0, 36)));
  }
  ID = ID + String.valueOf(System.currentTimeMillis());
  println(ID);
  
//acesso MQTT
  client = new MQTTClient(this);
  client.connect("tcp://broker.hivemq.com:1883", ID);
  client.subscribe("leitor");
  
  //colocacao das variaveis de som para o ficheiro recebido
  fft.input(M1);
  amp.input(M1);
  waveform.input(M1);
}

void draw() {
 
  fill(0, 30);
  rect(0, 0, width, height);
  
 
  float currentAmp = 0;
  
  if (M1.isPlaying() || M2.isPlaying()) { //se algum dos audios estiver a ser tocado
    
    //analise das variaveis de som
    fft.analyze(spectrum);
    waveform.analyze(waveformData);
    
    
    for (int i = 0; i < bands; i++) { //visualizacao mais suave
      lastSpectrum[i] = lerp(lastSpectrum[i], spectrum[i], smoothingFactor);
    }
    // amplitude atual
    currentAmp = amp.analyze();

  } 
      drawWaveform(waveformData, currentAmp); //desenha grafico
  }

void drawWaveform(float[] waveform, float amp) { //funcao para desenhar grafico com dados recebidos
  stroke(255);
  strokeWeight(2);
  
  float escala = map(amp, 0, 1, 100, 300);  //escala da waveform de acordo com a amplitude  cdddddddddddddddddf
  float ultimoX = 0;
  float ultimoY = height/2;
  
  for (int i = 0; i < waveform.length; i++) { //calculacao do x e y de cada barra
    float x = map(i, 0, waveform.length, 0, width);
    float y = height/2 + waveform[i] * escala;
    

    int colorIndex = int(map(abs(y - height/2), 0, escala, 0, colorPalette.length - 1));     //mapa da escolha da cor de acordo com a posicao e a amplitude
    colorIndex = constrain(colorIndex, 0, colorPalette.length - 1);
    color lineColor = colorPalette[colorIndex];
    
    stroke(lineColor);
    line(ultimoX, ultimoY, x, y);
    
    ultimoX = x;
    ultimoY = y;
  }
}

void messageReceived(String topic, byte[] payload) { //rececao das mensagens recebidas no MQTT
  String code = new String(payload);
  println(code);
  
  if (code.equals(n)) {
    if (!M1.isPlaying()) {
      M1.play();
      M2.stop();
      
      // Leitura dos elementos de som da M1
      fft.input(M1);
      waveform.input(M1);
      amp.input(M1);
    }
  }
  
  if (code.equals(n2)) {
    if (!M2.isPlaying()) {
      M2.play();
      M1.stop();
      
        // Leitura dos elementos de som da M2
      fft.input(M2);
      waveform.input(M2);
      amp.input(M2);
    }
  }
  
  if (code.equals(stop)) {
    M2.stop();
    M1.stop();
  }
}
