Controle de LEDs RGB e Display OLED com Joystick

Descrição
Este projeto foi desenvolvido utilizando a placa BitDogLab Raspberry Pi Pico. O objetivo principal é controlar os LEDs RGB e exibir um quadrado em um display OLED SSD1306, com base nas leituras dos eixos de um joystick. Além disso, são implementadas funcionalidades interativas para modificar o comportamento do display e controlar o PWM dos LEDs.

Funcionalidades Implementadas
Controle de Brilho dos LEDs RGB:

O LED azul tem seu brilho ajustado com base no eixo Y do joystick. Quanto mais o joystick se mover para cima ou para baixo, maior será o brilho do LED.
O LED vermelho tem seu brilho ajustado com base no eixo X do joystick. O movimento para a esquerda ou direita aumenta ou diminui o brilho do LED.
O brilho dos LEDs é controlado através de PWM (Pulse Width Modulation), permitindo transições suaves de intensidade.
Movimento de Quadrado no Display OLED:

Um quadrado de 8x8 pixels é movido no display OLED SSD1306, conforme os valores dos eixos X e Y do joystick. A posição do quadrado é atualizada a cada iteração, proporcionando uma interação visual com os movimentos do joystick.
Botões de Controle:

Botão do Joystick (BT_J): Alterna o estado do LED Verde e altera a borda do display, mudando entre diferentes estilos de moldura.
Botão A (BT_A): Alterna o status do PWM dos LEDs, ligando ou desligando o controle de brilho.
Botão B (BT_B): Reinicia o sistema e entra no modo bootloader.
Componentes Utilizados
LEDs RGB conectados às GPIOs 11, 12 e 13 para controle de brilho.
Botão do Joystick conectado à GPIO 22 para alternar entre os modos de borda e LED verde.
Joystick conectado às GPIOs 26 e 27 para controlar a posição do quadrado no display e os LEDs.
Botão A (BT_A) conectado à GPIO 5 para ativar/desativar o PWM dos LEDs.
Display SSD1306 conectado via I2C nas GPIOs 14 e 15.
Estrutura do Código
O código é dividido nas seguintes seções principais:

Configuração do Display: Inicialização do display OLED SSD1306 e configuração do I2C.
Controle de LEDs: Funções para ajustar o brilho dos LEDs RGB baseado nas leituras do joystick.
Movimento do Quadrado: Função que move um quadrado no display OLED com base nos eixos do joystick.
Interrupções: Funções associadas aos botões que controlam o estado do sistema, como alternar o LED verde, mudar a borda do display ou reiniciar o sistema.
Como Usar
Compile e carregue o código no seu Raspberry Pi Pico.
Conecte os componentes conforme o diagrama de pinagem fornecido.
Ao mover o joystick, observe o ajuste no brilho dos LEDs e o movimento do quadrado no display.
Pressione o Botão do Joystick para alternar o estado do LED verde e modificar a borda do display.
Pressione o Botão A para ativar ou desativar o controle PWM dos LEDs.
Pressione o Botão B para reiniciar o sistema.
Repositório
O código completo e mais detalhes sobre o projeto estão disponíveis no repositório do GitHub:

https://github.com/valtermsf90/tarefa_conversor_AD

Conclusão
Este projeto demonstra o uso de entradas analógicas e digitais para controlar LEDs RGB e exibir informações em um display OLED. Além disso, mostra como trabalhar com interrupções para interação com o usuário, criando uma experiência dinâmica e interativa.