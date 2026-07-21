#include <stdio.h>
#include <stdlib.h>

int main() {
    // PARTE 1: Declaracion de variables y constantes
    // 1. Enteros 
    int cantTurnos, t, op, codTurno, numOperarios, codOperario, pTotal, pMalas, pBuenas;
    
    // 2. Decimales / Flotantes (minimo 5)
    float pjeMalas, valProduccion, valMulta, valBono, valNeta;
    float tDinero, tMulta, tBono, tNeta, tEficiencia;
    float gDinero = 0.0f, gMulta = 0.0f, gBono = 0.0f, gNeta = 0.0f, gEficiencia = 0.0f, gPjeMalas = 0.0f;
    float promOperario = 0.0f, promTurno = 0.0f;
    
    // Acumuladores de conteo entero
    int tProd, tBuenas, tMalas, gProd = 0, gBuenas = 0, gMalas = 0, gOperarios = 0;
    int optMenu, i, j;

    // 3. Caracteres (minimo 2)
    char inicialSuper, enterDummy;

    // 4. Constantes (4)
    const float PRECIO_BUENA = 75.50f;
    const float PENALIZACION_MALAS = 15.25f;
    const float BONO_EFICIENCIA = 0.08f;
    const int MAX_DEFECTUOSAS = 10;

    printf("===========================================\n");
    printf(" SISTEMA METALMECANICA PANAMA S.A. \n");
    printf("===========================================\n\n");

    // PARTE 2: Solicitar turnos con do-while (entre 2 y 5)
    do {
        printf("Cantidad de turnos trabajados hoy (2-5): ");
        if (scanf("%d", &cantTurnos) != 1) {
            cantTurnos = 0; // Forzar fallo si se introduce un caracter
        }
        while (getchar() != '\n'); // Limpieza del buffer
        
        if (cantTurnos < 2 || cantTurnos > 5) {
            printf("Error: Debe ingresar un valor entero entre 2 y 5.\n");
        }
    } while (cantTurnos < 2 || cantTurnos > 5);

    // PARTE 3: Recorrer los turnos con ciclo for
    for (t = 1; t <= cantTurnos; t++) {
        // Reseteo de acumuladores del turno
        tProd = 0; tBuenas = 0; tMalas = 0;
        tDinero = 0.0f; tMulta = 0.0f; tBono = 0.0f; tNeta = 0.0f;

        printf("\n===========================================\n");
        printf("                TURNO %d\n", t);
        printf("===========================================\n");
        
        printf("Codigo del turno: ");
        scanf("%d", &codTurno);
        
        printf("Inicial del supervisor: ");
        scanf(" %c", &inicialSuper);

        // Validacion de operarios mediante while (5 a 20)
        printf("Cantidad de operarios (5-20): ");
        scanf("%d", &numOperarios);
        while (numOperarios < 5 || numOperarios > 20) {
            printf("Dato invalido. Reingrese cantidad de operarios (5-20): ");
            while (getchar() != '\n');
            scanf("%d", &numOperarios);
        }
        
        gOperarios += numOperarios; // Acumulador global de operarios

        // Ciclo for anidado para cada operario
        for (op = 1; op <= numOperarios; op++) {
            printf("\n--- Operario %d de %d ---\n", op, numOperarios);
            
            printf("Codigo de operario: ");
            scanf("%d", &codOperario);
            
            printf("Piezas producidas: ");
            scanf("%d", &pTotal);
            
            printf("Piezas defectuosas: ");
            scanf("%d", &pMalas);

            // Validacion: piezas defectuosas no pueden superar a las producidas
            while (pMalas < 0 || pMalas > pTotal) {
                printf("Error: Las piezas defectuosas no pueden ser mayores que las producidas (%d). Reintente: ", pTotal);
                scanf("%d", &pMalas);
            }

            // Calculos del operario
            pBuenas = pTotal - pMalas;
            pjeMalas = (pTotal > 0) ? ((float)pMalas / pTotal) * 100.0f : 0.0f;
            valProduccion = pBuenas * PRECIO_BUENA;
            valMulta = pMalas * PENALIZACION_MALAS;
            valBono = (pjeMalas < 2.0f) ? (valProduccion * BONO_EFICIENCIA) : 0.0f;
            valNeta = valProduccion + valBono - valMulta;

            // Clasificacion del desempeno del operario (if anidados)
            printf("Desempeno: ");
            if (pTotal > 120 && pjeMalas < 3.0f) {
                printf("Excelente\n");
            } else if (pTotal >= 90 && pTotal <= 120 && pjeMalas < 6.0f) {
                printf("Bueno\n");
            } else if (pTotal >= 70 && pTotal <= 89) {
                printf("Regular\n");
            } else {
                printf("Deficiente\n");
            }

            // Acumuladores del turno
            tProd += pTotal;
            tBuenas += pBuenas;
            tMalas += pMalas;
            tDinero += valProduccion;
            tMulta += valMulta;
            tBono += valBono;
            tNeta += valNeta;

            // Acumuladores globales
            gProd += pTotal;
            gBuenas += pBuenas;
            gMalas += pMalas;
            gDinero += valProduccion;
            gMulta += valMulta;
            gBono += valBono;
            gNeta += valNeta;
        }

        // PARTE 4: Menu interactivo del turno mediante switch
        int salirMenuTurno = 0;
        do {
            printf("\n--- MENU DEL TURNO %d ---\n", t);
            printf("1. Resumen del turno\n");
            printf("2. Eficiencia del turno\n");
            printf("3. Advertencias\n");
            printf("4. Continuar\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &optMenu);

            switch (optMenu) {
                case 1:
                    printf("\n[RESUMEN TURNO %d]\n", t);
                    printf("- Operarios procesados: %d\n", numOperarios);
                    printf("- Piezas producidas:   %d\n", tProd);
                    printf("- Piezas buenas:       %d\n", tBuenas);
                    printf("- Piezas defectuosas:  %d\n", tMalas);
                    printf("- Dinero generado:     B/.%.2f\n", tDinero);
                    break;

                case 2:
                    tEficiencia = (tProd > 0) ? ((float)tBuenas / tProd) * 100.0f : 0.0f;
                    printf("\n[EFICIENCIA TURNO %d]: %.2f%%\n", t, tEficiencia);
                    printf("Nivel: ");
                    if (tEficiencia >= 98.0f) {
                        printf("Excelente\n");
                    } else if (tEficiencia >= 95.0f) {
                        printf("Muy Buena\n");
                    } else if (tEficiencia >= 90.0f) {
                        printf("Aceptable\n");
                    } else {
                        printf("Critica\n");
                    }
                    break;

                case 3:
                    tEficiencia = (tProd > 0) ? ((float)tBuenas / tProd) * 100.0f : 0.0f;
                    printf("\n[ADVERTENCIAS TURNO %d]\n", t);
                    {
                        int hayAdvertencia = 0;
                        if (tMalas > MAX_DEFECTUOSAS) {
                            printf("! Alerta: Mas de 10 piezas defectuosas en el turno (%d).\n", tMalas);
                            hayAdvertencia = 1;
                        }
                        if (tProd < 500) {
                            printf("! Alerta: Produccion menor a 500 piezas (%d).\n", tProd);
                            hayAdvertencia = 1;
                        }
                        if (tEficiencia < 90.0f) {
                            printf("! Alerta: Eficiencia menor al 90%% (%.2f%%).\n", tEficiencia);
                            hayAdvertencia = 1;
                        }
                        if (tMulta > 250.0f) {
                            printf("! Alerta: Penalizaciones superan los B/.250.00 (B/.%.2f).\n", tMulta);
                            hayAdvertencia = 1;
                        }
                        if (!hayAdvertencia) {
                            printf("Sin advertencias. Operacion normal.\n");
                        }
                    }
                    break;

                case 4:
                    salirMenuTurno = 1;
                    break;

                default:
                    printf("Opcion invalida. Intente de nuevo.\n");
                    break;
            }
        } while (!salirMenuTurno);
    }

    // PARTE 5: Reporte General
    gPjeMalas = (gProd > 0) ? ((float)gMalas / gProd) * 100.0f : 0.0f;
    gEficiencia = (gProd > 0) ? ((float)gBuenas / gProd) * 100.0f : 0.0f;
    promOperario = (gOperarios > 0) ? (float)gProd / gOperarios : 0.0f;
    promTurno = (cantTurnos > 0) ? (float)gProd / cantTurnos : 0.0f;

    printf("\n===========================================\n");
    printf("     REPORTE GENERAL DE PRODUCCION         \n");
    printf("===========================================\n");
    printf("1.  Cantidad de turnos:            %d\n", cantTurnos);
    printf("2.  Total de operarios:            %d\n", gOperarios);
    printf("3.  Piezas producidas:             %d\n", gProd);
    printf("4.  Piezas buenas:                 %d\n", gBuenas);
    printf("5.  Piezas defectuosas:            %d\n", gMalas);
    printf("6.  Porcentaje general de defectos: %.2f%%\n", gPjeMalas);
    printf("7.  Total de bonos:                B/.%.2f\n", gBono);
    printf("8.  Total de penalizaciones:       B/.%.2f\n", gMulta);
    printf("9.  Ingreso bruto:                 B/.%.2f\n", gDinero);
    printf("10. Ingreso neto:                  B/.%.2f\n", gNeta);
    printf("11. Promedio prod. por operario:   %.2f\n", promOperario);
    printf("12. Promedio prod. por turno:      %.2f\n", promTurno);

    printf("\nEvaluacion General de la Empresa: ");
    if (gEficiencia >= 98.0f && gPjeMalas < 2.0f) {
        printf("Excelente\n");
    } else if (gEficiencia >= 95.0f) {
        printf("Muy Buena\n");
    } else if (gEficiencia >= 90.0f) {
        printf("Buena\n");
    } else if (gEficiencia >= 85.0f) {
        printf("Regular\n");
    } else {
        printf("Deficiente\n");
    }

    // REQUISITO FINAL: Patron de asteriscos usando unicamente `for` anidados
    printf("\nPatron grafico de turnos:\n");
    
    // Parte creciente (de 1 a cantTurnos)
    for (i = 1; i <= cantTurnos; i++) {
        for (j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
    // Parte decreciente (de cantTurnos-1 hasta 1)
    for (i = cantTurnos - 1; i >= 1; i--) {
        for (j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
