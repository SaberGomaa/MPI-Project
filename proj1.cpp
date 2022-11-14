#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<stdlib.h>
#include <cstdio>

const int MAX_SIZE = 100 ;
double Gpa(double Marks[] , int start , int endPoint  );

int GetInput(int my_rank , int comm_size ,int arr_size , double *Marks);

int main(){

    int my_rank , comm_size , arr_size ;
    int start = 0 , endP , n ;
    int Inc ;
    double PGPA , fGPA ;

    double Marks[MAX_SIZE] = {};


    MPI_Init(NULL , NULL) ;

    MPI_Comm_size(MPI_COMM_WORLD , &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD , &my_rank);

    arr_size = GetInput(my_rank , comm_size , arr_size , Marks);

    n = (arr_size+comm_size -1 ) / comm_size;

    start = n * my_rank ;
    endP = start+ n ;

    PGPA = Gpa(Marks , start , endP) ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //P to P   send & receve
   /* if(my_rank != 0 ){
        MPI_Send(&PGPA , 1 ,MPI_DOUBLE ,0 , 0 , MPI_COMM_WORLD );
    }
    else{
        fGPA = PGPA ;
        for(int i = 1 ; i < comm_size ; i++){
            MPI_Recv( &PGPA ,1 , MPI_DOUBLE, i , 0 , MPI_COMM_WORLD , MPI_STATUSES_IGNORE );
            fGPA += PGPA ;
        }
        fGPA /= arr_size ;

        printf("Total GPA = %f \n" , fGPA);
    }
*/

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // MPIReduce


/*

    MPI_Reduce(&PGPA , &fGPA , 1 , MPI_DOUBLE , MPI_SUM , 0 , MPI_COMM_WORLD);       // 7 arguments
    if(my_rank == 0){
        printf("Total GPA = %f \n" , fGPA/arr_size);
    }

*/
        // MPIAllreduce
        // remove distination

        MPI_Allreduce(&PGPA , &fGPA , 1 , MPI_DOUBLE , MPI_SUM  , MPI_COMM_WORLD);      //6 arguments
        printf("Total GPA = %f \n" , fGPA/arr_size);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MPI_Finalize();

    return 0 ;
}
/*
int GetInput(int my_rank , int comm_size ,int arr_size , double *marks ){

    if(my_rank == 0 ){
        printf("Enter Number of Courses ");
        fflush(stdout);
        scanf("%d", &arr_size );
        for(int i = 0 ; i < arr_size ; i++){
            printf("Enter Mark \n");
            fflush(stdout);
            scanf("%lf" , &marks[i]);
        }
        for(int i = 1 ; i<comm_size ; i++){
            MPI_Send(&marks , 1 , MPI_DOUBLE , i , 0 , MPI_COMM_WORLD);
        }
    }

    else{
     for(int i = 1 ; i<comm_size ; i++){
        MPI_Recv(&marks , 1 , MPI_DOUBLE , 0 , 0 , MPI_COMM_WORLD , MPI_STATUSES_IGNORE);
        }
    }

    return arr_size ;

}
*/



int GetInput(int my_rank , int comm_size ,int arr_size , double *marks ){

    if(my_rank == 0 ){
        printf("Enter Number of Courses ");
        fflush(stdout);
        scanf("%d", &arr_size );
        for(int i = 0 ; i < arr_size ; i++){
            printf("Enter Mark \n");
            fflush(stdout);
            scanf("%lf" , &marks[i]);
            }
    }

    MPI_Bcast(&marks , 1 , MPI_DOUBLE , 0 , MPI_COMM_WORLD); //5 argument

    return arr_size ;

}


double Gpa(double arr[] , int start , int endPoint){

        double g;

        for(int i = start ; i< endPoint ; i++){
            double p = arr[i] ;

            if (p >=90 && p <=100)
                g += 5.0;
            else if (p >=85 && p <=89)
                g += 4.5;
            else if (p >=80 && p <=84)
                g += 4.0;
            else if (p >=75 && p <=79)
                g += 3.5;
            else if(p >=70 && p <=74)
                g += 3.0;
            else if (p >=65 && p <=69)
                g += 2.5;
            else if (p >=60 && p <=64)
                g += 2.0;
            else if (p >=55 && p <=59)
                g += 1.5;
            else if (p >=50 && p <=54)
                g += 1.0;
            else if (p <50)
                g += 0.0;
    }
    return g;
}
