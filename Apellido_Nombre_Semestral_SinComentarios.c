// 
#include <stdio.h>
// 
#include <stdlib.h>

/*
 * Apellido, Nombre
 * Examen Semestral
 * 
 * --- VARIABLES ---
 * turn: 
 * i, j: 
 * codT, codO: 
 * cant: 
 * prod, def, buen: 
 * opc: 
 * pTur, bTur, dTur: 
 * pGen, bGen, dGen: 
 * tOpe: 
 * pDef: 
 * vPro: 
 * pena: 
 * bono: 
 * neta: 
 * diTu, peTu, boTu, neTu: 
 * diGe, peGe, boGe, neGe: 
 * efiT, efiG: 
 * pdGe: 
 * ppOp, ppTu: 
 * isup: 
 * fin: 
 */

int main() {
    // 1. Enteras (min 8)
    int turn, i, j, codT, cant, codO, prod, def, buen, opc;
    
    // 
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
    
    // PARTE 2
    // 
    do {
        printf("Ingrese turnos trabajados (2 a 5): "); scanf("%d", &turn);
        if(turn < 2 || turn > 5) printf("Error. Solo valores entre 2 y 5.\n\n");
    } while(turn < 2 || turn > 5);

    // PARTE 3
    for(i = 1; i <= turn; i++) {
        // 
        pTur=0; bTur=0; dTur=0; diTu=0.0; peTu=0.0; boTu=0.0; neTu=0.0;

        printf("\n----------------------------------\n REGISTRO DEL TURNO %d\n----------------------------------\nCodigo del turno: ", i);
        scanf("%d", &codT);
        printf("Inicial del supervisor: ");
        // 
        scanf(" %c", &isup);

        printf("Cantidad de operarios (5 a 20): "); scanf("%d", &cant);
        while(cant < 5 || cant > 20) {
            printf("Dato incorrecto. Operarios (5 a 20): "); scanf("%d", &cant);
        }
        tOpe += cant;

        for(j = 1; j <= cant; j++) {
            printf("\n  >>> Datos del Operario %d <<<\n  Codigo: ", j); scanf("%d", &codO);
            printf("  Piezas producidas: "); scanf("%d", &prod);
            printf("  Piezas defectuosas: "); scanf("%d", &def);
            
            // 
            while(def > prod) {
                printf("  Error: defectuosas superan a producidas.\n  Piezas defectuosas: "); scanf("%d", &def);
            }
            
            buen = prod - def; // 
            
            // 
            pDef = (prod > 0) ? ((float)def / prod) * 100.0 : 0.0;
            
            // 
            vPro = buen * PREC; // 
            pena = def * PENA;  // 
            
            // 
            bono = (pDef < 2.0) ? vPro * BONO : 0.0;
            neta = vPro + bono - pena; // 
            
            printf("\n  --- Resultados Operario %d ---\n  Piezas buenas: %d\n  Porcentaje de defectos: %.2f%%\n  Valor producido: B/.%.2f\n  Penalizacion: B/.%.2f\n  Produccion neta: B/.%.2f\n  Clasificacion: ", j, buen, pDef, vPro, pena, neta);
            
            if(prod > 120 && pDef < 3.0) printf("Excelente\n");
            else if(prod >= 90 && prod <= 120 && pDef < 6.0) printf("Bueno\n");
            else if(prod >= 70 && prod <= 89) printf("Regular\n");
            else printf("Deficiente\n");
            
            // 
            pTur += prod; bTur += buen; dTur += def; diTu += vPro; peTu += pena; boTu += bono; neTu += neta;
            pGen += prod; bGen += buen; dGen += def; diGe += vPro; peGe += pena; boGe += bono; neGe += neta;
        }
        
        // PARTE 4
        do {
            printf("\n==============================\n        MENU DEL TURNO        \n==============================\n1. Resumen del turno\n2. Eficiencia del turno\n3. Advertencias\n4. Continuar\nOpcion: ");
            scanf("%d", &opc);
            
            switch(opc) {
                case 1:
                    // 
                    printf("\n--- Resumen del turno ---\nOperarios procesados: %d\nPiezas producidas: %d\nPiezas buenas: %d\nPiezas defectuosas: %d\nDinero generado: B/.%.2f\n", cant, pTur, bTur, dTur, diTu); break;
                case 2:
                    // 
                    efiT = (pTur > 0) ? ((float)bTur / pTur) * 100.0 : 0.0;
                    printf("\nEficiencia del turno: %.2f%%\nClasificacion de la eficiencia: ", efiT);
                    if(efiT >= 98.0) printf("Excelente\n");
                    else if(efiT >= 95.0 && efiT < 98.0) printf("Muy Buena\n");
                    else if(efiT >= 90.0 && efiT < 95.0) printf("Aceptable\n");
                    else printf("Critica\n");
                    break;
                case 3:
                    // 
                    printf("\n--- Advertencias ---\n");
                    efiT = (pTur > 0) ? ((float)bTur / pTur) * 100.0 : 0.0;
                    if(dTur > MAXD) printf("- Mas de 10 piezas defectuosas en el turno.\n");
                    if(pTur < 500) printf("- Se han producido menos de 500 piezas.\n");
                    if(efiT < 90.0) printf("- La eficiencia del turno es menor al 90%%.\n");
                    if(peTu > 250.0) printf("- Las penalizaciones del turno superan B/.250.\n");
                    break;
                case 4: printf("Continuando...\n"); break;
                default: printf("Opcion incorrecta.\n");
            }
        } while(opc != 4);
    } 
    
    // PARTE 5
    // 
    pdGe = (pGen > 0) ? ((float)dGen / pGen) * 100.0 : 0.0; // 
    efiG = (pGen > 0) ? ((float)bGen / pGen) * 100.0 : 0.0; // 
    ppOp = (tOpe > 0) ? (float)pGen / tOpe : 0.0; // 
    ppTu = (turn > 0) ? (float)pGen / turn : 0.0; // 
    
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
    // 
    for(i = 1; i <= turn; i++) { for(j = 1; j <= i; j++) printf("*"); printf("\n"); }
    // 
    for(i = turn - 1; i >= 1; i--) { for(j = 1; j <= i; j++) printf("*"); printf("\n"); }

    printf("\nPresione Enter para salir...");
    while(getchar() != '\n'); // 
    getchar(); // 

    return 0;
}
