#include <stdio.h>
#include <stdlib.h>

int main() {
    // Declaracion de enteros
    int cantTurnos, t, op, codTurno, numOperarios, codOperario, pTotal, pMalas, pBuenas, optMenu;
    int tProd = 0, tBuenas = 0, tMalas = 0, gProd = 0, gBuenas = 0, gMalas = 0, gOperarios = 0;

    // Declaracion de flotantes
    float pjeMalas = 0.0f, valProduccion = 0.0f, valMulta = 0.0f, valBono = 0.0f, valNeta = 0.0f;
    float tDinero = 0.0f, tMulta = 0.0f, tBono = 0.0f, tNeta = 0.0f;
    float gDinero = 0.0f, gMulta = 0.0f, gBono = 0.0f, gNeta = 0.0f;
    float tEficiencia = 0.0f, gEficiencia = 0.0f, gPjeMalas = 0.0f, promOperario = 0.0f, promTurno = 0.0f;

    // Declaracion de caracteres
    char inicialSuper, teclaExit;

    // Declaracion de constantes
    const float PRECIO_BASE = 75.50f, MULTA_DEF = 15.25f, TASA_BONO = 0.08f;
    const int LIMITE_MALAS = 10;

    printf("===========================================\n SISTEMA METALMECANICA \n===========================================\n\n");

    // Pedir turnos con filtro anti-letras usando while infinito
    printf("Cantidad de turnos (2-5): ");
    while(1) {
        if(scanf("%d", &cantTurnos) == 1 && cantTurnos >= 2 && cantTurnos <= 5) break; // Sale si esta correcto
        printf("Dato erroneo. Intenta de nuevo (2-5): ");
        while(getchar() != '\n'); // Vacia el buffer si escribio letras
    }

    t = 1;
    // Bucle para iterar sobre la cantidad de turnos
    while(t <= cantTurnos) {
        // Reseteo de variables locales del turno
        tProd = 0; tBuenas = 0; tMalas = 0; tDinero = 0.0f; tMulta = 0.0f; tBono = 0.0f; tNeta = 0.0f;

        printf("\n--- TURNO %d ---\nCodigo numerico: ", t);
        while(1) { // Verifica codigo anti letras
            if(scanf("%d", &codTurno) == 1 && codTurno > 0) break;
            printf("Reingresa codigo: "); while(getchar() != '\n');
        }
        
        printf("Inicial supervisor: ");
        scanf(" %c", &inicialSuper); // Captura letra saltando los enters

        printf("Operarios activos (5-20): ");
        while(1) { // Verifica rango de operarios de forma segura
            if(scanf("%d", &numOperarios) == 1 && numOperarios >= 5 && numOperarios <= 20) break;
            printf("Error en operarios: "); while(getchar() != '\n');
        }
        gOperarios += numOperarios; // Acumula global

        op = 1;
        // Bucle de lectura de datos de empleados
        while(op <= numOperarios) {
            printf("\nOperario %d | Codigo: ", op); 
            while(1) { if(scanf("%d", &codOperario) == 1 && codOperario > 0) break; printf("Error. Cod: "); while(getchar() != '\n'); }
            
            printf("Total fabricado: "); 
            while(1) { if(scanf("%d", &pTotal) == 1 && pTotal >= 0) break; printf("Error. Total: "); while(getchar() != '\n'); }
            
            printf("Total defectuoso: "); 
            while(1) { // Control logico de defectos (sin letras y menor al total)
                if(scanf("%d", &pMalas) == 1 && pMalas >= 0 && pMalas <= pTotal) break;
                printf("Invalido. Reintenta: "); while(getchar() != '\n');
            }
            
            pBuenas = pTotal - pMalas; // Operacion matematica simple
            pjeMalas = (pTotal > 0) ? ((float)pMalas / pTotal) * 100.0f : 0.0f; // Regla de 3
            
            // Aplicacion de costos y penalidades
            valProduccion = pBuenas * PRECIO_BASE;
            valMulta = pMalas * MULTA_DEF;
            valBono = (pjeMalas < 2.0f) ? (valProduccion * TASA_BONO) : 0.0f; // Solo si es bueno gana bono
            valNeta = valProduccion + valBono - valMulta;
            
            printf("-> OK: %d, Malas: %.1f%%, Neto: B/.%.2f\n-> Rendimiento: ", pBuenas, pjeMalas, valNeta);
            // Categorizacion de operario
            if(pTotal > 120 && pjeMalas < 3.0f) printf("Excelente\n");
            else if(pTotal >= 90 && pTotal <= 120 && pjeMalas < 6.0f) printf("Bueno\n");
            else if(pTotal >= 70 && pTotal <= 89) printf("Regular\n");
            else printf("Deficiente\n");
            
            // Sumar a los acumuladores
            tProd += pTotal; tBuenas += pBuenas; tMalas += pMalas;
            tDinero += valProduccion; tMulta += valMulta; tBono += valBono; tNeta += valNeta;
            gProd += pTotal; gBuenas += pBuenas; gMalas += pMalas;
            gDinero += valProduccion; gMulta += valMulta; gBono += valBono; gNeta += valNeta;
            
            op++; // Siguiente operario
        }
        
        // Despliegue de menu interactivo
        while(1) {
            printf("\n[1] Resumen [2] Efic [3] Alertas [4] Salir turno\nSeleccione: ");
            while(1) { // Proteccion del menu
                if(scanf("%d", &optMenu) == 1) break;
                printf("Error de menu: "); while(getchar() != '\n');
            }
            
            if(optMenu == 1) { // Usamos if else if en lugar de switch para variar un poco la logica
                printf("Resumen: %d procesados, %d prod, %d ok, %d malas, B/.%.2f bruto\n", numOperarios, tProd, tBuenas, tMalas, tDinero);
            } else if(optMenu == 2) {
                tEficiencia = (tProd > 0) ? ((float)tBuenas / tProd) * 100.0f : 0.0f; // Calculo de eficiencia local
                printf("Eficiencia: %.2f%%\nNivel: ", tEficiencia);
                if(tEficiencia >= 98.0f) printf("Excelente\n");
                else if(tEficiencia >= 95.0f) printf("Muy Buena\n");
                else if(tEficiencia >= 90.0f) printf("Aceptable\n");
                else printf("Critica\n");
            } else if(optMenu == 3) {
                tEficiencia = (tProd > 0) ? ((float)tBuenas / tProd) * 100.0f : 0.0f;
                printf("Alertas de turno:\n"); // Reporta todas las que se cumplan segun las variables acumuladas
                if(tMalas > LIMITE_MALAS) printf("- Defectos elevados\n");
                if(tProd < 500) printf("- Baja cuota de produccion\n");
                if(tEficiencia < 90.0f) printf("- Eficiencia critica\n");
                if(tMulta > 250.0f) printf("- Multiples penalizaciones\n");
            } else if(optMenu == 4) {
                break; // Rompe el menu y avanza
            } else {
                printf("Opcion errada.\n");
            }
        }
        t++; // Siguiente turno
    } 
    
    // Promedios finales generales del dia
    gPjeMalas = (gProd > 0) ? ((float)gMalas / gProd) * 100.0f : 0.0f;
    gEficiencia = (gProd > 0) ? ((float)gBuenas / gProd) * 100.0f : 0.0f;
    promOperario = (gOperarios > 0) ? (float)gProd / gOperarios : 0.0f;
    promTurno = (cantTurnos > 0) ? (float)gProd / cantTurnos : 0.0f;
    
    printf("\n--- INFORME GENERAL ---\n");
    printf("Turnos: %d | Ops: %d | Prod: %d | OK: %d | Malas: %d (%.2f%%)\n", cantTurnos, gOperarios, gProd, gBuenas, gMalas, gPjeMalas);
    printf("Bonos: B/.%.2f | Penal: B/.%.2f | Bruto: B/.%.2f | Neto: B/.%.2f\n", gBono, gMulta, gDinero, gNeta);
    printf("Prom. Op: %.2f | Prom. Turno: %.2f\n", promOperario, promTurno);
    
    printf("Estado General: "); // Evaluacion final de gerencia
    if(gEficiencia >= 98.0f && gPjeMalas < 2.0f) printf("Excelente\n");
    else if(gEficiencia >= 95.0f) printf("Muy Buena\n");
    else if(gEficiencia >= 90.0f) printf("Buena\n");
    else if(gEficiencia >= 85.0f) printf("Regular\n");
    else printf("Deficiente\n");
    
    // Impresion de patron usando while iterativo
    printf("\nPatron grafico:\n");
    t = 1;
    while(t <= cantTurnos) { // Creciente (arriba a centro)
        op = 1; while(op <= t) { printf("*"); op++; } printf("\n"); t++;
    }
    t = cantTurnos - 1;
    while(t >= 1) { // Decreciente (centro a abajo)
        op = 1; while(op <= t) { printf("*"); op++; } printf("\n"); t--;
    }

    printf("\nPresione Enter...");
    while(getchar() != '\n'); // Limpieza de terminal
    getchar(); // Espera tecla real
    return 0;
}
