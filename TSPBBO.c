#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_CITIES 1000
#define MAX_ITERATIONS 5000
#define MIGRATION_RATE 0.25
#define MUTATION_RATE 0.05

int num_cities;
double distance[MAX_CITIES][MAX_CITIES];
int population[MAX_CITIES][MAX_CITIES];
int best_path[MAX_CITIES];
int worst_path[MAX_CITIES];
double best_cost;
double worst_cost;
int initialized[MAX_CITIES][MAX_CITIES] = {0};

double calculate_cost(int path[]) {
    double cost = 0;
    for (int i = 0; i < num_cities - 1; i++) {
        cost += distance[path[i]][path[i + 1]];
    }
    cost += distance[path[num_cities - 1]][path[0]];
    return cost;
}

void migration(int population[][MAX_CITIES]) {
    for (int i = 0; i < num_cities; i++) {
        int r1 = rand() % num_cities;
        int r2 = rand() % num_cities;
        if (rand() / (double) RAND_MAX < MIGRATION_RATE) {
            for (int j = 0; j < num_cities; j++) {
                int temp = population[r1][j];
                population[r1][j] = population[r2][j];
                population[r2][j] = temp;
            }
        }
    }
}



void mutation(int population[][MAX_CITIES]) { 
    for (int i = 0; i < num_cities; i++) {
        if (rand() / (double) RAND_MAX < MUTATION_RATE) {
        	
            int r1 = rand() % num_cities;
            int r2 = rand() % num_cities;
            
            int temp = population[i][r1];
            population[i][r1] = population[i][r2];
            population[i][r2] = temp;
        }
    }
}

void init_population() {
    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
            population[i][j] = j;
        }
        for (int j = 0; j < num_cities - 1; j++) {
            int r = rand() % (num_cities - j) + j;
            int temp = population[i][j];
            population[i][j] = population[i][r];
            population[i][r] = temp;
        }
    }
}

int main() {
	system("color F4");
	num_cities=1;
	
	while(num_cities>0){
    srand(time(NULL));

    printf("                           <-------------------------->\n\n");
    printf("  Enter the number of cities: ");
    scanf("%d", &num_cities);
    if(num_cities<=0)break;
    printf("  *--------------------------*\n\n");
    printf("  Enter the distance matrix: \n");
    printf("\n  ---->\n");
    
    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
        	if(i==j){
        		distance[i][j]=0;
        		printf("  Enter the distance between city [%d] and city [%d] : %lf \n", i, j,distance[i][j]);
        		continue;
			}
			if(initialized[i][j]==1){
        		distance[i][j]=distance[j][i];
        		printf("  Enter the distance between city [%d] and city [%d] : %lf \n", i, j,distance[i][j]);
        		continue;
			}do{
        	printf("  Enter the distance between city [%d] and city [%d] : ",i,j);
        	 scanf("%lf", &distance[i][j]);
			 if (distance[i][j]<0){
			 printf("  Error! \n  A negative distance, please re-enter a positive value\n");}
			 }while(distance[i][j]<0); 
			
			 
            initialized[i][j] = 1;
            initialized[j][i] = 1;
            
        }
         printf("\n");
    }
    init_population();
    
    best_cost = calculate_cost(population[0]);
    worst_cost = calculate_cost(population[0]);
    
    for (int i = 0; i < num_cities; i++) {
        best_path[i] = population[0][i];
        worst_path[i] = population[0][i];
        
    }
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        migration(population);
        mutation(population);
        for (int j = 0; j < num_cities; j++) {
            double cost = calculate_cost(population[j]);
            
            
            if (cost > worst_cost) {
                worst_cost = cost;
                for (int k = 0; k < num_cities; k++) {
                    worst_path[k] = population[j][k];
                }
			}
            if (cost < best_cost) {
                best_cost = cost;
                for (int k = 0; k < num_cities; k++) {
                    best_path[k] = population[j][k];
                }
            }
        }
    }
    printf("  *--------------------------*\n");
    
    printf("  Worst path: ");
    for (int i = 0; i < num_cities; i++) {
    	if(i==num_cities-1){
		printf("%d --> %d", worst_path[i], worst_path[0]); continue;
		}
        printf("%d --> ", worst_path[i]);
    }
    printf("\n  Worst cost: %lf \n", worst_cost);
    
    printf("  *--------------------------*\n");
    printf("  Best path : ");
    for (int i = 0; i < num_cities; i++) {
    	if(i==num_cities-1){
		printf("%d --> %d", best_path[i], best_path[0]); continue;
		}
        printf("%d --> ", best_path[i]);
    }
    printf("\n  Best cost : %lf", best_cost);
    printf("\n  *--------------------------*\n\n");
    
    system("  pause");
    system("cls");
    }
    return 0;
}






