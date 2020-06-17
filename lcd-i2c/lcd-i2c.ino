

/*-importacao Necessaria*/
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

/*Declaracao de Constates e Objetos*/
// seta o Endereco do Display LCD  0x27 
// Seta os pinos do I2C usado (padrao da biblioteca)
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 16,2);  // Set the LCD I2C address

void setup()   {
  Serial.begin(9600);  //Serial

// inicializa o lcd de 16 caracters e 2 linhas
lcd.init();
lcd.begin(16,2);   

// ------- Um breve blink de backlight (luz de fundo  -------------
    //liga 
    lcd.backlight();
    delay(250);
    //desliga
    lcd.noBacklight();
    delay(250);
    
    //finaliza com a luz de fundo ligada
    lcd.backlight(); 
 
   
}


void loop() {

        //-------- Escritura dos caracteres no display ------------------
        //Nota : Posicao do Curso (Caracter, Linha) começa no 0 
        //Inicia com o ponteiro na linha 0
        lcd.setCursor(0,0); 
        // Limpa o Display
        lcd.clear();
        //Escreve
        lcd.print(" Bienvenidos al"); 
        //Pula para segunda linha na posicao 0
        lcd.setCursor(0,1);
        //Escreve
        lcd.print("Aula Inteligente");
        //aguarda 5 segundos
        delay(5000);
        // Limpa o Display para escrever novo texto
        lcd.clear();
        //Reposiciona o cursor na linha 0 e coluna 0
        lcd.setCursor(0,0);
        //Escreve
        lcd.print("Visite a Loja");
        //Pula para segunda linha na posicao 0
        lcd.setCursor(0,1);
        //Escreve
        lcd.print("TECNODUINO.COM");
        //Aguarda 8 segundos para reiniciar o loop
        delay(8000); 
        
}
