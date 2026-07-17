#include <stdio.h>
#include <stdlib.h>

int main() {
    /* Declaracion de 8 enteros, puestas en miniatura para ahorrar espacio */
    int n_turnos, iter_1, iter_2, id_turno, n_operarios, id_ope, p_total, p_malas, p_buenas, m_opcion;
    /* Acumuladores del turno y del dia enteros */
    int t_prod=0, t_buen=0, t_mal=0, d_prod=0, d_buen=0, d_mal=0, total_ope=0;
    
    /* Declaracion de 5 decimales */
    float porc_m=0.0, gan_bruta=0.0, descuento=0.0, premio=0.0, gan_neta=0.0;
    /* Acumuladores del turno y del dia decimales (plata) */
    float t_bruto=0.0, t_desc=0.0, t_pre=0.0, t_neto=0.0;
    float d_bruto=0.0, d_desc=0.0, d_pre=0.0, d_neto=0.0;
    float efi_t=0.0, efi_d=0.0, porc_d=0.0, prom_ope=0.0, prom_tur=0.0;

    /* Declaracion de caracteres para menues */
    char supervisor, tecla_fin;

    /* Constantes de cobros (lo que paga la empresa por pieza, multa y % bono) */
    const float C_PREC=75.50, C_PENA=15.25, C_BONO=0.08;
    const int C_MAXD=10;

    printf("************************************************\n");
    printf("*             SISTEMA DE PLANTA                *\n");
    printf("************************************************\n\n");
    
    /* Bucle hasta que el profe ponga un numero correcto */
    do {
        printf("Ingrese turnos (2 a 5): ");
        int leido = scanf("%d", &n_turnos); // Guardamos la respuesta en leido
        if(leido == 1 && n_turnos >= 2 && n_turnos <= 5) break; /* Si esta bien y es numero, rompe el ciclo */
        printf("Incorrecto, letras o rango invalido.\n");
        while(getchar() != '\n'); /* Borrar letras de la memoria para que no se trabe */
    } while(1);

    /* Recorrido de los turnos */
    for(iter_1 = 1; iter_1 <= n_turnos; iter_1++) {
        /* Encera los totales de turno a 0 para que no se sumen los del turno pasado */
        t_prod=0; t_buen=0; t_mal=0; t_bruto=0.0; t_desc=0.0; t_pre=0.0; t_neto=0.0;

        printf("\n>>> REGISTRO TURNO %d <<<\nCodigo de turno: ", iter_1);
        /* Valida codigo usando la tecnica de lectura segura */
        do {
            if(scanf("%d", &id_turno) == 1 && id_turno > 0) break;
            printf("Error en codigo: "); while(getchar() != '\n');
        } while(1);

        printf("Inicial de supervisor: ");
        scanf(" %c", &supervisor); /* Lee un solo caracter, el espacio evita errores */

        printf("Cantidad de operarios (5-20): ");
        /* Valida la cant. de operarios con filtro de letras */
        do {
            if(scanf("%d", &n_operarios) == 1 && n_operarios >= 5 && n_operarios <= 20) break;
            printf("Cantidad erronea: "); while(getchar() != '\n');
        } while(1);
        total_ope += n_operarios; /* Acumula a la variable maestra de operarios totales */

        /* Recorrido de los operarios de este turno especifico */
        for(iter_2 = 1; iter_2 <= n_operarios; iter_2++) {
            printf("\nOp #%d - Codigo: ", iter_2); 
            do { if(scanf("%d", &id_ope) == 1 && id_ope > 0) break; printf("Error: "); while(getchar()!='\n'); } while(1);

            printf("Producidas: "); 
            do { if(scanf("%d", &p_total) == 1 && p_total >= 0) break; printf("Error: "); while(getchar()!='\n'); } while(1);
            
            printf("Defectuosas: "); 
            /* Filtra que las malas jamas superen a las que produjo en total */
            do { if(scanf("%d", &p_malas) == 1 && p_malas >= 0 && p_malas <= p_total) break; printf("Error logico: "); while(getchar()!='\n'); } while(1);
            
            p_buenas = p_total - p_malas; /* Saca buenas restandole las malas */
            porc_m = (p_total > 0) ? ((float)p_malas / p_total) * 100.0 : 0.0; /* Saca porcentaje multiplicando por 100 */
            gan_bruta = p_buenas * C_PREC; /* Multiplica buenas por precio base */
            descuento = p_malas * C_PENA; /* Descuento por hacerlas mal */
            premio = (porc_m < 2.0) ? gan_bruta * C_BONO : 0.0; /* Condicion de bono: menos del 2% */
            gan_neta = gan_bruta + premio - descuento; /* Suma las ganancias y resta las deudas */
            
            printf("Buenas: %d | Malas: %.2f%% | Pago: B/.%.2f\nClasificacion: ", p_buenas, porc_m, gan_neta);
            /* Categorias de empleados basado en su produccion y fallos */
            if(p_total > 120 && porc_m < 3.0) printf("Excelente\n");
            else if(p_total >= 90 && p_total <= 120 && porc_m < 6.0) printf("Bueno\n");
            else if(p_total >= 70 && p_total <= 89) printf("Regular\n");
            else printf("Deficiente\n");
            
            /* Sumas de turno (reinician cada que cambia de turno) */
            t_prod += p_total; t_buen += p_buenas; t_mal += p_malas; t_bruto += gan_bruta; t_desc += descuento; t_pre += premio; t_neto += gan_neta;
            /* Sumas del dia (estas nunca se reinician, van directo al reporte final) */
            d_prod += p_total; d_buen += p_buenas; d_mal += p_malas; d_bruto += gan_bruta; d_desc += descuento; d_pre += premio; d_neto += gan_neta;
        }
        
        /* Subsistema de menu */
        do {
            printf("\n--- MENU ---\n1. Resumen\n2. Eficiencia\n3. Advertencias\n4. Continuar\nSeleccion: ");
            do { if(scanf("%d", &m_opcion) == 1) break; printf("Opcion falsa: "); while(getchar()!='\n'); } while(1);
            
            switch(m_opcion) {
                case 1:
                    printf("Ops: %d | Piezas: %d | Buenas: %d | Defectos: %d | Dinero: B/.%.2f\n", n_operarios, t_prod, t_buen, t_mal, t_bruto); break;
                case 2:
                    efi_t = (t_prod > 0) ? ((float)t_buen / t_prod) * 100.0 : 0.0; /* Saca eficacia local dividiendo buenas entre total */
                    printf("Eficiencia: %.2f%% (", efi_t);
                    if(efi_t >= 98.0) printf("Excelente)\n");
                    else if(efi_t >= 95.0) printf("Muy Buena)\n");
                    else if(efi_t >= 90.0) printf("Aceptable)\n");
                    else printf("Critica)\n");
                    break;
                case 3:
                    efi_t = (t_prod > 0) ? ((float)t_buen / t_prod) * 100.0 : 0.0;
                    printf("Avisos:\n"); /* Revisa todas las variables acumuladas del turno usando if's individuales */
                    if(t_mal > C_MAXD) printf(" * Demasiados defectos\n");
                    if(t_prod < 500) printf(" * Produccion escasa\n");
                    if(efi_t < 90.0) printf(" * Eficiencia reprobable\n");
                    if(t_desc > 250.0) printf(" * Alta penalizacion\n");
                    break;
                case 4: printf("Avanzando...\n"); break;
                default: printf("Opcion no existe.\n");
            }
        } while(m_opcion != 4);
    } 
    
    /* Resultados globales finales despues de acabar todos los turnos */
    porc_d = (d_prod > 0) ? ((float)d_mal / d_prod) * 100.0 : 0.0; /* Frecuencia de falla global de todo el dia */
    efi_d = (d_prod > 0) ? ((float)d_buen / d_prod) * 100.0 : 0.0; /* Eficacia global en % */
    prom_ope = (total_ope > 0) ? (float)d_prod / total_ope : 0.0; /* Media general dividida entre todos los operarios */
    prom_tur = (n_turnos > 0) ? (float)d_prod / n_turnos : 0.0; /* Media general dividida entre la cantidad de turnos */
    
    printf("\n################################################\n");
    printf("1. Turnos totales: %d\n2. Operarios totales: %d\n3. Piezas totales: %d\n", n_turnos, total_ope, d_prod);
    printf("4. Piezas utiles: %d\n5. Defectos totales: %d\n6. %% de defectos: %.2f%%\n", d_buen, d_mal, porc_d);
    printf("7. Bonos: B/.%.2f\n8. Descuentos: B/.%.2f\n9. Bruto: B/.%.2f\n10. Neto: B/.%.2f\n", d_pre, d_desc, d_bruto, d_neto);
    printf("11. Prom/Operario: %.2f\n12. Prom/Turno: %.2f\n", prom_ope, prom_tur);
    
    printf("\nEvaluacion corporativa: "); /* Veredicto final tomando en cuenta piezas malas de toda la fabrica */
    if(efi_d >= 98.0 && porc_d < 2.0) printf("Excelente\n");
    else if(efi_d >= 95.0) printf("Muy Buena\n");
    else if(efi_d >= 90.0) printf("Buena\n");
    else if(efi_d >= 85.0) printf("Regular\n");
    else printf("Deficiente\n");
    
    /* Patrones graficos */
    printf("\nGrafico requerido:\n");
    for(iter_1 = 1; iter_1 <= n_turnos; iter_1++) { /* Asciende haciendo escaleras hacia arriba */
        for(iter_2 = 1; iter_2 <= iter_1; iter_2++) printf("*"); printf("\n");
    }
    for(iter_1 = n_turnos - 1; iter_1 >= 1; iter_1--) { /* Desciende haciendo escaleras al revés */
        for(iter_2 = 1; iter_2 <= iter_1; iter_2++) printf("*"); printf("\n");
    }

    printf("\n[PRESIONE ENTER PARA FINALIZAR]");
    while(getchar() != '\n'); /* Borra enter colgado para que no se salte el getchar de abajo */
    getchar(); /* Cierra */
    return 0;
}
