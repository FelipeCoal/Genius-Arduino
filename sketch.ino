
//Genius
//definições
#define TS 5 // Para subir a dificuldade basta aumentar o valor de TS.
#define LED_2 2
#define LED_3 3
#define LED_4 4
#define BOTAO_2 10
#define BOTAO_3 11
#define BOTAO_4 12

//inicialização de variáveis
int sequenciaBotoes[TS];
int numerodarodada = 1;
int rodada = 0;
enum Etapas {GERAR_RODADA, PLAYER_JOGANDO, VITORIA, DERROTA,};
int respostas = 0;
int sequencia[TS];

void setup() {
  Serial.begin(9600);
  delay(1000);
  iniciaPortas();
  iniciaJogo();
}

void loop() {
  switch (etapaAtual()) {
    case GERAR_RODADA:
      delay(500);
      Serial.print("Rodada ");
      Serial.print(numerodarodada);
      Serial.print("\r\n");
      iniciacaoRodada();
      break;

    case PLAYER_JOGANDO:
      Serial.println("Selecine a cor");
      contaJogadasPlayer();
      break;

    case VITORIA:
      Serial.println("Você venceu");
      fim();
      break;

    case DERROTA:
      Serial.println("Você perdeu");
      fim();
      break;
  }
  //delay(500);
}
//Determinar Etapa do Jogo
int etapaAtual() {
  if (rodada <= TS & respostas < TS) {
    if (respostas == rodada) {
      return GERAR_RODADA;
    } else {
      //contaJogadasPlayer();
      return PLAYER_JOGANDO;
    }
  } else if (rodada <= TS & respostas == TS) {
    return VITORIA;
  }
  else {
    return DERROTA;
  }
}
//Inicia variáveis da rodada
void iniciacaoRodada() {
  rodada++;
  numerodarodada = 1;
  respostas = 0;
  sequenciaJogo();
}
//Apresenta a sequência a ser seguida
void sequenciaJogo() {
  for (int indice = 0; indice < rodada; indice++) {
    ativaLed(sequencia[indice]);
  }
}
//Conta número de acertos durante a rodada
void contaJogadasPlayer() {
  //while(respostas<=rodada){
  int resposta = botaoClicado();
  if (resposta == sequencia[respostas]) {
    respostas++;
    numerodarodada++;
  } else {
    Serial.println("Cor errada");
    rodada = TS + 2;
    //return DERROTA;
    //}
  }
}
// Identifica botões clicados
int botaoClicado() {
  int x = 0;
  while (x == 0) {
    if (digitalRead(BOTAO_2) == LOW) {
      return ativaLedRapido(LED_2);
      x = 1;
    }
    if (digitalRead(BOTAO_3) == LOW) {
      return ativaLedRapido(LED_3);
      x = 1;
    }
    if (digitalRead(BOTAO_4) == LOW) {
      return ativaLedRapido(LED_4);
      x = 1;
    }
  }
  return;
}
//Determina a sequência dos LEDs com base em TS
void iniciaJogo() {
  int jogo = analogRead(0);
  randomSeed(jogo);
  for (int indice = 0; indice < TS; indice++)
    sequencia[indice] = sorteiaCor();
}
//Sorteia a cor para cada índice da list TS
int sorteiaCor() {
  return random(LED_2, LED_4 + 1);
}
//Inicia as portas LED/BOTAO
void iniciaPortas() {
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(BOTAO_2, INPUT_PULLUP);
  pinMode(BOTAO_3, INPUT_PULLUP);
  pinMode(BOTAO_4, INPUT_PULLUP);
}
//LEDs de sinalização do fim vitória/derrota.
void fim() {
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);
  digitalWrite(LED_4, HIGH);
  delay(1000);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  exit(0);
}
//Ativação de LED
int ativaLed(int portaLed) {
  digitalWrite(portaLed, HIGH);
  delay(1000);
  digitalWrite(portaLed, LOW);
  delay(200);
  return portaLed;
}
//Ativação rádida de LED
int ativaLedRapido(int portaLed) {
  digitalWrite(portaLed, HIGH);
  delay(200);
  digitalWrite(portaLed, LOW);
  return portaLed;
}

/*Serial.println(x)
  Mostra o que ocorre com o elemento x no painel Serial.*/