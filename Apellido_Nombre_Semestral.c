// <stdio.h> (Standard Input/Output) es obligatoria porque contiene las funciones para interactuar con la consola: printf(), scanf() y getchar().
#include <stdio.h>
// <stdlib.h> (Standard Library) es una buena practica en C. En este codigo especifico no se usa, pero los profesores suelen pedirla para utilidades del sistema.
#include <stdlib.h>

/*
 * Apellido, Nombre
 * Examen Semestral
 * 
 * --- DICCIONARIO DE VARIABLES ---
 * turn: cantidad de turnos ingresados
 * i, j: contadores usados para dar vueltas en los ciclos for
 * codT, codO: codigo de identificacion del turno y del operario
 * cant: cantidad de operarios trabajando en un turno
 * prod, def, buen: cantidad de piezas producidas, defectuosas y buenas (por operario)
 * opc: almacena el numero de la opcion elegida en el menu
 * pTur, bTur, dTur: acumuladores de piezas totales, buenas y defectuosas del turno
 * pGen, bGen, dGen: acumuladores de piezas totales, buenas y defectuosas generales del dia
 * tOpe: suma del numero total de operarios registrados
 * pDef: porcentaje de piezas defectuosas del operario
 * vPro: dinero generado (valor producido) por el operario
 * pena: dinero descontado por penalizaciones al operario
 * bono: dinero extra otorgado como bono al operario
 * neta: ganancia neta final del operario
 * diTu, peTu, boTu, neTu: acumuladores de dinero, penalizaciones, bonos y ganancia neta del turno
 * diGe, peGe, boGe, neGe: acumuladores de dinero, penalizaciones, bonos y ganancia neta general
 * efiT, efiG: porcentaje de eficiencia del turno y eficiencia general de la empresa
 * pdGe: porcentaje de piezas defectuosas a nivel general
 * ppOp, ppTu: promedios de piezas producidas por operario y por turno
 * isup: caracter que guarda la inicial del supervisor
 * fin: se usa al final unicamente para esperar que el usuario presione Enter
 */

int main() {
    // 1. Enteras (min 8)
    int turn, i, j, codT, cant, codO, prod, def, buen, opc;
    
    // Acumuladores de turno y generales
    int pTur=0, bTur=0, dTur=0, pGen=0, bGen=0, dGen=0, tOpe=0;
    
    // 2. Decimales (min 5)
    float pDef=0.0, vPro=0.0, pena=0.0, bono=0.0, neta=0.0;
    float diTu=0.0, peTu=0.0, boTu=0.0, neTu=0.0;
    float diGe=0.0, peGe=0.0, boGe=0.0, neGe=0.0;
    float efiT=0.0, efiG=0.0, pdGe=0.0, ppOp=0.0, ppTu=0.0;

    // 3. Caracteres (min 2)
    char isup, fin;

    // 4. Constantes
    const float PREC=75.50, PENA=15.25, BONO=0.08;
    const int MAXD=10;

    printf("================================================\n SISTEMA DE PRODUCCION - METALMECANICA PANAMA \n================================================\n\n");
    
    // PARTE 2: Validacion de entrada a prueba de letras y rangos
    printf("Ingrese turnos trabajados (2 a 5): "); 
    // scanf != 1 asegura que el usuario escribio un numero y no una letra.
    while(scanf("%d", &turn) != 1 || turn < 2 || turn > 5) {
        printf("Error. Ingrese un numero valido entre 2 y 5: ");
        while(getchar() != '\n'); // Limpia el buffer (evita ciclos infinitos si el usuario ingresa letras)
    }

    // PARTE 3: Damos una vuelta por cada turno registrado
    for(i = 1; i <= turn; i++) {
        // Resetear acumuladores a 0 al iniciar para no mezclar datos con turnos anteriores
        pTur=0; bTur=0; dTur=0; diTu=0.0; peTu=0.0; boTu=0.0; neTu=0.0;

        printf("\n----------------------------------\n REGISTRO DEL TURNO %d\n----------------------------------\nCodigo del turno: ", i);
        while(scanf("%d", &codT) != 1 || codT <= 0) { // Evita letras y codigos negativos o nulos
            printf("Error. Ingrese un codigo numerico valido y positivo: ");
            while(getchar() != '\n');
        }

        printf("Inicial del supervisor: ");
        scanf(" %c", &isup); // El espacio en " %c" limpia automaticamente cualquier salto de linea previo

        printf("Cantidad de operarios (5 a 20): "); 
        while(scanf("%d", &cant) != 1 || cant < 5 || cant > 20) {
            printf("Error. El dato es incorrecto. Operarios (5 a 20): "); 
            while(getchar() != '\n');
        }
        tOpe += cant;

        for(j = 1; j <= cant; j++) {
            printf("\n  >>> Datos del Operario %d <<<\n  Codigo: ", j); 
            while(scanf("%d", &codO) != 1 || codO <= 0) {
                printf("  Error. Codigo numerico valido: ");
                while(getchar() != '\n');
            }

            printf("  Piezas producidas: "); 
            while(scanf("%d", &prod) != 1 || prod < 0) {
                printf("  Error. Cantidad numerica valida mayor o igual a cero: ");
                while(getchar() != '\n');
            }

            printf("  Piezas defectuosas: "); 
            // Validamos letras, negativos y el error logico de reportar mas malas que producidas
            while(scanf("%d", &def) != 1 || def < 0 || def > prod) {
                printf("  Error: Valor invalido o defectuosas superan a producidas.\n  Piezas defectuosas: "); 
                while(getchar() != '\n');
            }
            
            buen = prod - def; // Resta basica para obtener las buenas
            
            // Calculo de porcentaje de defectos (Regla de tres)
            pDef = (prod > 0) ? ((float)def / prod) * 100.0 : 0.0;
            
            // Calculos de dinero
            vPro = buen * PREC; // Ganancia
            pena = def * PENA;  // Descuento
            
            // El bono solo aplica si tuvo menos del 2% de errores
            bono = (pDef < 2.0) ? vPro * BONO : 0.0;
            neta = vPro + bono - pena; // Produccion neta final
            
            printf("\n  --- Resultados Operario %d ---\n  Piezas buenas: %d\n  Porcentaje de defectos: %.2f%%\n  Valor producido: B/.%.2f\n  Penalizacion: B/.%.2f\n  Produccion neta: B/.%.2f\n  Clasificacion: ", j, buen, pDef, vPro, pena, neta);
            
            if(prod > 120 && pDef < 3.0) printf("Excelente\n");
            else if(prod >= 90 && prod <= 120 && pDef < 6.0) printf("Bueno\n");
            else if(prod >= 70 && prod <= 89) printf("Regular\n");
            else printf("Deficiente\n");
            
            // Sumamos resultados del operario a los acumuladores del TURNO y GENERALES
            pTur += prod; bTur += buen; dTur += def; diTu += vPro; peTu += pena; boTu += bono; neTu += neta;
            pGen += prod; bGen += buen; dGen += def; diGe += vPro; peGe += pena; boGe += bono; neGe += neta;
        }
        
        // PARTE 4
        do {
            printf("\n==============================\n        MENU DEL TURNO        \n==============================\n1. Resumen del turno\n2. Eficiencia del turno\n3. Advertencias\n4. Continuar\nOpcion: ");
            while(scanf("%d", &opc) != 1) { // Control contra letras en la eleccion del menu
                printf("Error. Ingrese una opcion numerica valida: ");
                while(getchar() != '\n');
            }
            
            switch(opc) {
                case 1:
                    // Muestra las variables sumadas de este turno
                    printf("\n--- Resumen del turno ---\nOperarios procesados: %d\nPiezas producidas: %d\nPiezas buenas: %d\nPiezas defectuosas: %d\nDinero generado: B/.%.2f\n", cant, pTur, bTur, dTur, diTu); break;
                case 2:
                    // Eficiencia (buenas vs total)
                    efiT = (pTur > 0) ? ((float)bTur / pTur) * 100.0 : 0.0;
                    printf("\nEficiencia del turno: %.2f%%\nClasificacion de la eficiencia: ", efiT);
                    if(efiT >= 98.0) printf("Excelente\n");
                    else if(efiT >= 95.0 && efiT < 98.0) printf("Muy Buena\n");
                    else if(efiT >= 90.0 && efiT < 95.0) printf("Aceptable\n");
                    else printf("Critica\n");
                    break;
                case 3:
                    // Alertas usando if simples (revisa todas las condiciones, no solo una)
                    printf("\n--- Advertencias ---\n");
                    efiT = (pTur > 0) ? ((float)bTur / pTur) * 100.0 : 0.0;
                    if(dTur > MAXD) printf("- Mas de 10 piezas defectuosas en el turno.\n");
                    if(pTur < 500) printf("- Se han producido menos de 500 piezas.\n");
                    if(efiT < 90.0) printf("- La eficiencia del turno es menor al 90%%.\n");
                    if(peTu > 250.0) printf("- Las penalizaciones del turno superan B/.250.\n");
                    break;
                case 4: printf("Continuando...\n"); break;
                default: printf("Opcion incorrecta. Elija 1, 2, 3 o 4.\n");
            }
        } while(opc != 4);
    } 
    
    // PARTE 5
    // Promedios y porcentajes generales (se calculan con los acumuladores totales)
    pdGe = (pGen > 0) ? ((float)dGen / pGen) * 100.0 : 0.0; // Porcentaje de defectos general
    efiG = (pGen > 0) ? ((float)bGen / pGen) * 100.0 : 0.0; // Eficiencia general
    ppOp = (tOpe > 0) ? (float)pGen / tOpe : 0.0; // Promedio por operario
    ppTu = (turn > 0) ? (float)pGen / turn : 0.0; // Promedio por turno
    
    printf("\n==============================================\n        REPORTE GENERAL DE PRODUCCION         \n==============================================\n");
    printf("1. Cantidad de turnos: %d\n2. Total de operarios: %d\n3. Piezas producidas: %d\n4. Piezas buenas: %d\n5. Piezas defectuosas: %d\n6. Porcentaje general de defectos: %.2f%%\n", turn, tOpe, pGen, bGen, dGen, pdGe);
    printf("7. Total de bonos: B/.%.2f\n8. Total de penalizaciones: B/.%.2f\n9. Ingreso bruto: B/.%.2f\n10. Ingreso neto: B/.%.2f\n11. Promedio prod. por operario: %.2f\n12. Promedio prod. por turno: %.2f\n", boGe, peGe, diGe, neGe, ppOp, ppTu);
    
    printf("\n>>> Evaluacion general: ");
    if(efiG >= 98.0 && pdGe < 2.0) printf("Excelente <<<\n");
    else if(efiG >= 95.0) printf("Muy Buena <<<\n");
    else if(efiG >= 90.0) printf("Buena <<<\n");
    else if(efiG >= 85.0) printf("Regular <<<\n");
    else printf("Deficiente <<<\n");
    
    // REQUISITO FINAL
    printf("\nPatron de turnos:\n");
    // Parte de arriba de la flecha: va sumando asteriscos por fila
    for(i = 1; i <= turn; i++) { for(j = 1; j <= i; j++) printf("*"); printf("\n"); }
    // Parte de abajo de la flecha: va restando asteriscos por fila
    for(i = turn - 1; i >= 1; i--) { for(j = 1; j <= i; j++) printf("*"); printf("\n"); }

    printf("\nPresione Enter para salir...");
    while(getchar() != '\n'); // Limpiamos el buffer de entrada de forma estandar
    getchar(); // Espera a que el usuario presione Enter

    return 0;
}
