

//Programa: Modulo MP3 DFPlayer Mini com Arduino
//Autor: Arduino e Cia

/***************************************************
  DFPlayer - A Mini MP3 Player For Arduino
 ***************************************************
  Created 2016-12-07
  By [Angelo qiao](Angelo.qiao@dfrobot.com)

  GNU Lesser General Public License.
  See <http://www.gnu.org/licenses/> for details.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Inicia a serial por software nos pinos 10 e 11
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

//Objeto responsável pela comunicação com o módulo MP3 (DFPlayer Mini)
DFRobotDFPlayerMini myDFPlayer;

//variável responsável por armazenar os comandos enviados para controlar o player
String buf;
//variável responsável por armazenar o estado do player (0: tocando ; 1: pausado)
int pausa = 0;
//variável responsável por armazenar o estado da equalização
//varia de 0 a 5
int equalizacao = 0;
//variável responsável por armazenar o total de músicas presentes no SD card.
int maxSongs = 0;

void setup()
{
  //Comunicacao serial com o modulo
  mySoftwareSerial.begin(9600);
  //Inicializa a serial do Arduino
  Serial.begin(115200);

  //Verifica se o modulo esta respondendo e se o
  //cartao SD foi encontrado
  Serial.println();
  Serial.println("DFRobot DFPlayer Mini");
  Serial.println("Inicializando modulo DFPlayer... (3~5 segundos)");
  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println("Nao inicializado:");
    Serial.println("1.Cheque as conexoes do DFPlayer Mini");
    Serial.println("2.Insira um cartao SD");
    while (true);
  }
  Serial.println();
  Serial.println("Modulo DFPlayer Mini inicializado!");

  //Definicoes iniciais
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.volume(10); //Volume 10
  myDFPlayer.EQ(0); //Equalizacao normal

  //recupera o numero de Músicas encontradas no SD.
  maxSongs = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD);
  Serial.println();
  Serial.print("Numero de arquivos no cartao SD: ");
  Serial.println(maxSongs);
  
  //Mostra o menu de comandos
  menu_opcoes();
}

void loop()
{
  //Aguarda a entrada de dados pela serial
  while (Serial.available() > 0)
  {
    //recupera os dados de entrada
    buf = Serial.readStringUntil('\n');
    
    //Reproducao
    if ((buf.toInt() >= 1) && (buf.toInt() <= maxSongs))
    {
      Serial.print("Reproduzindo musica: ");
      Serial.println(buf.toInt());
//      buf = buf - 48;
      myDFPlayer.play(buf.toInt());
      menu_opcoes();
    }
    
    //Parada
    if (buf == "s")
    {
      myDFPlayer.stop();
      Serial.println("Musica parada!");
      menu_opcoes();
    }
    
    //Pausa/Continua a musica
    if (buf == "p")
    {
      pausa = !pausa;
      if (pausa == 0)
      {
        Serial.println("Continua musica...");
        myDFPlayer.start();
      }
      if (pausa == 1)
      {
        Serial.println("Musica pausada...");
        myDFPlayer.pause();
      }
      menu_opcoes();
    }
    
    //Seleciona equalizacao
    if (buf == "e")
    {
      equalizacao++;
      if (equalizacao == 6)
      {
        equalizacao = 0;
      }
      myDFPlayer.EQ(equalizacao);
      Serial.print("Equalizacao: ");
      Serial.print(equalizacao);
      Serial.println(" (0 = Normal, 1 = Pop, 2 = Rock, 3 = Jazz, 4 = Classic, 5 = Bass)");
      menu_opcoes();
    }
    
    //Aumenta volume
    if (buf == "+")
    {
      myDFPlayer.volumeUp();
      Serial.print("Volume atual:");
      Serial.println(myDFPlayer.readVolume());
      menu_opcoes();
    }
    
    //Diminui volume
    if (buf == "-")
    {
      myDFPlayer.volumeDown();
      Serial.print("Volume atual:");
      Serial.println(myDFPlayer.readVolume());
      menu_opcoes();
    }
  }
}

void menu_opcoes()
{
  Serial.println();
  Serial.println("Comandos:");
  Serial.print(" [1-");
  Serial.print(maxSongs);
  Serial.println("] Para selecionar o arquivo MP3");
  Serial.println(" [s] parar reproducao");
  Serial.println(" [p] pausa/continua a musica");
  Serial.println(" [e] seleciona equalizacao");
  Serial.println(" [+ or -] aumenta ou diminui o volume");
  Serial.println();
}
