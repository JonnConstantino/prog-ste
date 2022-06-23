# IFSC STE 2022.1 - Programação de Sistemas Embarcados

## Descrição

Com base nos componentes desenvolvidos em aula e disponibilizados através do GitHub Classroom, modelar um sistema que:

* Adquira a cada minuto a leitura analógica de um potenciômetro (sugestão: utilizar um timer calibrado para 1 minuto como trigger do ADC);
* Faça um filtro FIR de ordem 8 dessas medições;
* Receba os coeficientes do FIR via UART;
* Imprima via UART, a cada medição, o valor atualizado da saída do filtro;
* Utilize uma FIFO para a entrada de dados do ADC;
* Utilize uma FIFO de saída (tx) e outra FIFO para entrada (rx) da UART;