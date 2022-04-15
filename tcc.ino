#include <Wire.h>        //Biblioteca para manipulação do protocolo I2C
#include <DS3231.h>    //Biblioteca para manipulação do DS3231
#include <IOXhop_FirebaseESP32.h>
#include <WiFi.h> 

#define FIREBASE_HOST "https://senaitcc-dbfc1-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "7xGw14DVSJNkzHv9qyWY0o4W2YubT8CP8CulenD0"
#define WIFI_SSID "WIFI_ADM_CFP117"                   
#define WIFI_PASSWORD "CnF@Pm1!1j7@AfD3Mt"

int soma = 0;

int horas =0, seg =0, seg2 =0, mn= 0;
DS3231 rtc;
RTCDateTime dataehora; 
  
void setup()
{
  Serial.begin(115200);     //Inicialização da comunicação serial
  rtc.begin();            //Inicialização do RTC DS3231
  rtc.setDateTime(__DATE__, __TIME__);   //Configurando valores iniciais 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conectando");
  while (WiFi.status() !=WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("conectado");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(17, INPUT);
}
void loop()
{
if (digitalRead(17) == HIGH)
  soma = soma + 1;
  Serial.println(soma);
  {  static unsigned long ult_tempo = 0;
  int tempo = millis();
  if((tempo - ult_tempo) >= 1000)
  {
  ult_tempo = tempo;
  seg++; seg2++;
  Firebase.setFloat("Morpheuzada/TEMPO DE USO/segundos", seg2);
  Firebase.setFloat("Morpheuzada/TEMPO DE USO/minutos", mn);
  Firebase.setFloat("Morpheuzada/TEMPO DE USO/horas", horas);
  Firebase.setInt("Morpheuzada/PECAS/PECAS_CONTADAS", soma);
}
  if(seg >= 60)
{
  seg =0;
  seg2 =0;
  horas =0;
  mn++;

  if(mn >= 60)
 {
  seg =0;
  seg2 =0;
  mn =0;
  horas++;
 }
}{
dataehora = rtc.getDateTime();     
  Firebase.setInt("Morpheuzada/RTC/minutos", dataehora.minute);
  Firebase.setInt("Morpheuzada/RTC/horas", dataehora.hour);
  Firebase.setInt("Morpheuzada/RTC/segundos", dataehora.second);
  Firebase.setInt("RTC/minutos", dataehora.minute); 
  Firebase.setInt("RTC/segundos", dataehora.second); 
  Firebase.setInt("RTC/horas", dataehora.hour); 
  delay(1000);
 }}}
 
