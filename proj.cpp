#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<stdlib.h>

double Gpa(double Marks[] , int start , int endPoint  );

int main(){

    int my_rank , comm_size , arr_size = 6  ;
    int start = 0 , endP  ;
    int Inc , n;
    double PGPA , fGPA;
    double Marks[arr_size] = {55 , 80 , 90 , 70 , 80 , 95};


    //////
    MPI_Init(NULL , NULL) ;

    MPI_Comm_size(MPI_COMM_WORLD , &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD , &my_rank);


    n = (arr_size+comm_size -1 ) / comm_size;

    start = n * my_rank ;
    endP = start+ n ;

   /*
    start = (arr_size / comm_size) * my_rank ;
    endP = start+ (arr_size / comm_size) ;

    */

    PGPA = Gpa(Marks , start , endP) ;

    //printf("GPA = %f \n" , PGPA);


    //P to P

/*
    if(my_rank != 0 ){
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



  // MPIReduce


    MPI_Reduce(&PGPA , &fGPA , 1 , MPI_DOUBLE , MPI_SUM , 0 , MPI_COMM_WORLD);
    if(my_rank == 0){
        printf("Total GPA = %f \n" , fGPA/arr_size);
    }

/*
        // MPIAllreduce
        // remove distination

        MPI_Allreduce(&PGPA , &fGPA , 1 , MPI_DOUBLE , MPI_SUM  , MPI_COMM_WORLD);
        printf("Total GPA = %f \n" , fGPA/arr_size);


*/



    MPI_Finalize();

    return 0 ;
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
/*

double Gpa(double arr[] , int arr_size){

    double fGpa = 0 ;

    for(int i = 0 ; i< arr_size ; i++)
    {
        if(arr[i] >= 90 ){
            fGpa += 4 ;
        }
        else if(arr[i] >= 80){
            fGpa += 3 ;
        }
        else {
            fGpa += 1 ;
        }
    }

    return double(fGpa / arr_size) ;

}

*/
