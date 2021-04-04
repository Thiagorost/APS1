#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "aps5-e7174-default-rtdb.firebaseio.com" // Link da pagina do firebase, projeto.
#define FIREBASE_AUTH "UkLU5GNkWknCYqbH9PIcQJmA0KakuVuArgYvA4H7" // sua chave de segurança, contas de serviço
#define WIFI_SSID "teste"      // Nome do seu wifi
#define WIFI_PASSWORD "123456789"  // senha do seu wifi

FirebaseData firebaseData;  

int fireStatus;   // criamos uma variavel de status
int led = D1;    // Selecionamos a porta que vamos acionar
void setup() {   
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);    // informamos que o led d1 vai ser uma saida   
  pinMode(led, OUTPUT);               // informamos que o led d1 vai ser uma saida 
  digitalWrite(led, LOW);                             // o led vai estar desligado
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                 // conecta ao wifi
  Serial.print("Connecting to ");                 // verificação
  Serial.print(WIFI_SSID);                        // printf ssid
  while (WiFi.status() != WL_CONNECTED) {          // printf do status da conexão
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");      
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt(firebaseData, "led", 0);
}

void loop() {
  if(Firebase.getInt(firebaseData, "/led"))    // vamos puxar as informações do firebase a partir do getint.
  {
    fireStatus = firebaseData.intData();             
    if (fireStatus == 1) {                      // nada mais que if e else
      Serial.println("Led Turned ON");                         
      digitalWrite(LED_BUILTIN, LOW);               
        digitalWrite(led, HIGH);                    // liga led
    } 
    else if (fireStatus == 0) {
      Serial.println("Led Turned OFF");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(led, LOW);
    }
    else {
      Serial.println("Wrong Credential! Please send ON/OFF");
    }
  }
}
