#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [ 조정호 ]  [ 2020039032 ] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row); // row x col 행렬 3개 생성

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //비정상종ㄹㅛ

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col); //a, b 행렬을 0 ~ 19 무작위 수로 채움
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); // 행렬 a, b를 출력
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); // 행렬  a와 b를 더함
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); // 행렬 a에서 b를 뺌
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 행렬 a의 전치행렬 matrix_a_t를 구하고 출력
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col); // 행렬 matrix_a와 matrix_a_t를 곱함
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col); //동적할당 해제
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); //q를 눌러 종료할때까지 메뉴 출력 > 동작수행 계속 반복

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    int **matrix = (int **)malloc(sizeof(int*)*row);//입력받은 row만큼 행 생성

    for (int i = 0; i < row; i++) 
        matrix[i] = (int *)malloc(sizeof(int)*col); //입력받은 col만큼 열 생성
    
    return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    for(int i=0; i<row; i++){                   //행
        for(int j=0; j<col; j++){               //열
            printf("%d\t", matrix[i][j]);       //행렬의 요소 하나씩 출력
        }
        printf("\n");
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    for(int i=0; i<row; i++){                   //행
        for(int j=0; j<col; j++)                //열
            free(matrix[i][j]);                 //free 동적할당
    }
    free(matrix);

    return 0;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    for(int i = 0; i < row; i++){              //행
        for(int j = 0; j < col; j++){          //열
            srand(time(NULL)); 
            matrix [i][j] = rand()%19;         //19까지의 난수 생성 후 대입
        }
    }

    return 0;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int **matrix_sum = (int**)malloc(sizeof(int*)*row);
    for(int i = 0; i<row; i++){
        matrix_sum[i] = (int*)malloc(sizeof(int)*col);
    }//행렬의 합을 저장할 행렬 matrix_sum 생성

    for(int i =0; i<row; i++){                                  //행
        for(int j=0; j<col; j++){                               //열
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //더한값 저장
        }
    }
    return matrix_sum;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int **matrix_sub = (int**)malloc(sizeof(int*)*row);
    for(int i = 0; i<row; i++){
        matrix_sub[i] = (int*)malloc(sizeof(int)*col);
    }//행렬의 합을 저장할 또 하나의 행렬 생성

    for(int i =0; i<row; i++){                                  //행
        for(int j=0; j<col; j++){                               //열
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; //뺀 값 저장
        }
    }

    return matrix_sub;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
int** matrix_t = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++)
        matrix_t[i] = (int*)malloc(sizeof(int) * col); //전치행렬 저장할 배열 생성

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            matrix_t[i][j] = matrix[j][i];             //i, j 뒤바꾸면 전치행렬 완성
    }
    return matrix_t;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int **matrix_axt = (int**)malloc(sizeof(int*) * row);
    for(int i=0; i<row; i++)
        matrix_axt[i] = (int*)malloc(sizeof(int) * col);//행렬 곱을 저장할 새로운 배열 생성
    

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            int result = 0;
            for(int n=0; n<row; n++){
                result += matrix_a[i][n]*matrix_t[n][j]; //행렬 곱 계산
            }
            matrix_axt[i][j] = result; //값 대입
        }
    }

    return matrix_axt;

}

