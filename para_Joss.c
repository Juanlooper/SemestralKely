#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Definiciones Base, con nombres de variables descriptivos como pedia el profe
    int t_turnos, i_turno, i_ope;               // Controladores de flujo de los bucles
    int cod_t, c_opes, cod_o;                   // Variables de identificacion numerica
    int f_total, f_malas, f_buenas, opc;        // Estadisticas puras locales (del momento)
    
    int act_prod=0, act_buen=0, act_mal=0;      // Acumuladores parciales (reinician en cada turno)
    int acg_prod=0, acg_buen=0, acg_mal=0, acg_opes=0; // Acumuladores generales de todo el dia (no reinician nunca)
    
    float porc_mal=0.0f, v_prod=0.0f, v_multa=0.0f, v_bono=0.0f, v_neto=0.0f; // Variables de calculo de dinero para 1 operario
    float act_din=0.0f, act_mul=0.0f, act_bon=0.0f, act_net=0.0f;             // Totales de caja del turno
    float acg_din=0.0f, acg_mul=0.0f, acg_bon=0.0f, acg_net=0.0f;             // Totales de caja del dia
    float efi_t=0.0f, efi_g=0.0f, porc_mal_g=0.0f, pro_ope=0.0f, pro_tur=0.0f; // Los KPI (Porcentajes finales)

    char c_gerente, t_salida;                   // Caracteres utiles

    const float PR_UNIT = 75.50f, MULTA = 15.25f, T_BONO = 0.08f; // Costos y descuentos fijos
    const int LIMITE = 10;                      // Control tope

    printf("==================================================\n   SOFTWARE DE GESTION PANAMA   \n==================================================\n\n");
    
    // Asegurar que el usuario no meta letras o numeros fuera de rango (2-5)
    printf("Dime los turnos (2 a 5): ");
    while(scanf("%d", &t_turnos) != 1 || (t_turnos < 2 || t_turnos > 5)) {
        while(getchar() != '\n'); // Saca la basura del teclado si ponen letras en vez de numeros
        printf("Error: Mete un numero del 2 al 5: ");
    }

    // Iniciamos la captura para cada turno
    for(i_turno = 1; i_turno <= t_turnos; i_turno++) {
        act_prod = 0; act_buen = 0; act_mal = 0; // Se encera los contadores del turno a cero
        act_din = 0.0f; act_mul = 0.0f; act_bon = 0.0f; act_net = 0.0f; 

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n   DATOS DEL TURNO %d   \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nIdentificador del turno: ", i_turno);
        while(scanf("%d", &cod_t) != 1 || cod_t <= 0) { // Valida que no se tipeen letras o id negativos
            while(getchar() != '\n'); printf("No valido: ");
        }

        printf("Letra de Supervisor: ");
        scanf(" %c", &c_gerente); // Toma un solo caracter, tiene espacio para limpiar salto de linea

        printf("Conteo de operarios (5 a 20): ");
        while(scanf("%d", &c_opes) != 1 || (c_opes < 5 || c_opes > 20)) { // Validacion que previene crash del programa
            while(getchar() != '\n'); printf("Invalido, de 5 a 20: ");
        }
        acg_opes += c_opes; // Guardamos y acumulamos la cantidad para el reporte general

        // Loop sobre los trabajadores, dependemos de c_opes (la cantidad)
        for(i_ope = 1; i_ope <= c_opes; i_ope++) {
            printf("\n   [ Operario %d ]\n   ID: ", i_ope); 
            while(scanf("%d", &cod_o) != 1) { while(getchar() != '\n'); printf("   Mal ID: "); }

            printf("   Unidades: "); 
            while(scanf("%d", &f_total) != 1 || f_total < 0) { while(getchar() != '\n'); printf("   Error: "); } // Sin letras ni negativos
            
            printf("   Averiadas: "); 
            while(scanf("%d", &f_malas) != 1 || f_malas < 0 || f_malas > f_total) { // Un control logico: no reportar mas averias que lo que produjo
                while(getchar() != '\n'); printf("   Error, no pueden superar las unidades: "); 
            }
            
            f_buenas = f_total - f_malas; // Hacemos la deduccion
            porc_mal = (f_total > 0) ? ((float)f_malas / f_total) * 100.0f : 0.0f; // Saca el porcentaje de daño (regla de 3)
            v_prod = f_buenas * PR_UNIT; // Dinero generado sumando las piezas buenas
            v_multa = f_malas * MULTA; // Dinero multado multiplicando las malas
            v_bono = (porc_mal < 2.0f) ? (v_prod * T_BONO) : 0.0f; // Bono bajo condicion, se usa if en una linea (ternario)
            v_neto = v_prod + v_bono - v_multa; // Pago neto: le damos su plata y su bono, y le quitamos la multa
            
            printf("   -> Validas: %d | Averias: %.2f%% | Neto: B/.%.2f\n   -> Evaluacion: ", f_buenas, porc_mal, v_neto);
            // Categorizacion simple, se imprime enseguida en lugar de guardarlo en variable (Si hace menos de 70 = Deficiente por regla general)
            if(f_total > 120 && porc_mal < 3.0f) printf("Excelente\n");
            else if(f_total >= 90 && f_total <= 120 && porc_mal < 6.0f) printf("Bueno\n");
            else if(f_total >= 70 && f_total <= 89) printf("Regular\n");
            else printf("Deficiente\n");
            
            // Sumatoria al bloque turno (suman a los totales del momento)
            act_prod += f_total; act_buen += f_buenas; act_mal += f_malas;
            act_din += v_prod; act_mul += v_multa; act_bon += v_bono; act_net += v_neto;
            
            // Sumatoria al bloque dia (suman a la estadistica de toda la corrida del programa)
            acg_prod += f_total; acg_buen += f_buenas; acg_mal += f_malas;
            acg_din += v_prod; acg_mul += v_multa; acg_bon += v_bono; acg_net += v_neto;
        }
        
        // Despliegue de panel por cada vez que acaba la revision del turno
        do {
            printf("\n   === OPCIONES DEL TURNO %d ===\n   [1] Cifras\n   [2] Eficiencia\n   [3] Alertas\n   [4] Seguir\n   [5] Terminar programa\n   Opcion: ", i_turno);
            while(scanf("%d", &opc) != 1) { while(getchar() != '\n'); printf("   Error: "); } // Filtrar basuras de letras
            
            switch(opc) {
                case 1:
                    printf("\n   Cifras: Ops: %d | Total: %d | Validas: %d | Averiadas: %d | Monto: B/.%.2f\n", c_opes, act_prod, act_buen, act_mal, act_din); break;
                case 2:
                    efi_t = (act_prod > 0) ? ((float)act_buen / act_prod) * 100.0f : 0.0f; // Saca la eficiencia dividiendo lo bueno entre el total %
                    printf("\n   Eficiencia: %.2f%% -> Nivel: ", efi_t);
                    if(efi_t >= 98.0f) printf("Excelente\n");
                    else if(efi_t >= 95.0f) printf("Muy Buena\n");
                    else if(efi_t >= 90.0f) printf("Aceptable\n");
                    else printf("Critica\n");
                    break;
                case 3:
                    efi_t = (act_prod > 0) ? ((float)act_buen / act_prod) * 100.0f : 0.0f;
                    printf("\n   Alertas:\n"); // Revisamos variables del turno, if separados para mostrar multiple errores a la vez
                    int alarmas_activas = 0;
                    if(act_mal > LIMITE) { printf("   [!] Muchas averias.\n"); alarmas_activas = 1; }
                    if(act_prod < 500) { printf("   [!] Deficit productivo.\n"); alarmas_activas = 1; }
                    if(efi_t < 90.0f) { printf("   [!] Rendimiento critico.\n"); alarmas_activas = 1; }
                    if(act_mul > 250.0f) { printf("   [!] Sobrecosto.\n"); alarmas_activas = 1; }
                    if(!alarmas_activas) printf("   [OK] No hay problemas que reportar.\n");
                    break;
                case 4: printf("   Procediendo...\n"); break;
                case 5: printf("   Cerrando el sistema abruptamente...\n"); exit(0);
                default: printf("   No reconocida.\n");
            }
        } while(opc != 4);
    } 
    
    // Matematicas Finales para el reporte general que se imprime una sola vez
    porc_mal_g = (acg_prod > 0) ? ((float)acg_mal / acg_prod) * 100.0f : 0.0f; // % global
    efi_g = (acg_prod > 0) ? ((float)acg_buen / acg_prod) * 100.0f : 0.0f; // Eficacia global
    pro_ope = (acg_opes > 0) ? (float)acg_prod / acg_opes : 0.0f; // Promedio operario: total dividio entre numero de operarios
    pro_tur = (t_turnos > 0) ? (float)acg_prod / t_turnos : 0.0f; // Promedio turno: total dividio entre cantidad de turnos
    
    printf("\n==================================================\n         BOLETIN ESTADISTICO FINAL         \n==================================================\n");
    printf("1. Turnos registrados: %d\n2. Fuerza laboral: %d\n", t_turnos, acg_opes);
    printf("3. Volumen prod: %d\n4. Volumen valido: %d\n5. Volumen averiado: %d\n6. Indice averias: %.2f%%\n", acg_prod, acg_buen, acg_mal, porc_mal_g);
    printf("7. Bonos: B/.%.2f\n8. Multas: B/.%.2f\n9. Brutos: B/.%.2f\n10. Netos: B/.%.2f\n", acg_bon, acg_mul, acg_din, acg_net);
    printf("11. Media/ope: %.2f\n12. Media/turno: %.2f\n", pro_ope, pro_tur);
    
    printf("\n>>> Calificacion Corporativa: "); // Toma en cuenta todo
    if(efi_g >= 98.0f && porc_mal_g < 2.0f) printf("Excelente <<<\n");
    else if(efi_g >= 95.0f) printf("Muy Buena <<<\n");
    else if(efi_g >= 90.0f) printf("Buena <<<\n");
    else if(efi_g >= 85.0f) printf("Regular <<<\n");
    else printf("Deficiente <<<\n");
    
    // Grafica asteriscos mediante iteracion cruzada
    printf("\nGrafico:\n");
    for(i_turno = 1; i_turno <= t_turnos; i_turno++) {
        for(i_ope = 1; i_ope <= i_turno; i_ope++) printf("*"); // Piramide creciendo al limite de los turnos
        printf("\n");
    }
    for(i_turno = t_turnos - 1; i_turno >= 1; i_turno--) {
        for(i_ope = 1; i_ope <= i_turno; i_ope++) printf("*"); // Piramide bajando invirtiendo for externo
        printf("\n");
    }

    printf("\nFin. Enter para cerrar.");
    while(getchar() != '\n'); // Descarga buffer que haya sobrado de la ultima letra
    getchar(); // Funcion de detencion
    return 0;
}
