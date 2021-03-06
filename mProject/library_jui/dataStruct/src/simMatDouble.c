#include "simMatDouble.h"
#include <stdio.h>

vector_double new_vector_double(unsigned int size)
{
    vector_double data ={0,0};
    if(size > 0)
    {
        data.data = (double*)malloc(sizeof(double)*size);
        if(data.data != NULL) 
        {
            data.lenght = size;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }
    return data;
}
matrix_double new_matrix_double(unsigned int row,unsigned int col)
{
    int i=0;
    matrix_double data = {0,0,0};
    if(row ==0 || col==0) return data;

    data.data = (double**)malloc(sizeof(double*)*row);
    if(data.data ==NULL) return data;

    data.row =row;
    data.col =col;
    for(i=0;i<data.row;i++)
    {
        data.data[i] =NULL;
        data.data[i] = (double*)malloc(sizeof(double)*col);
        if(data.data[i] ==NULL) data.col--;
    }
    return data;
}
void delete_vector_double(vector_double *rhs)
{
    if(rhs!=NULL)
    {
        if( rhs->lenght >0 && rhs->data!=0)
        {
            free(rhs->data);
            rhs->data=0;
            rhs->lenght=0;
        }
    }
    else
    {
        /* do nothing */
    }
}
void delete_matrix_double(matrix_double *rhs)
{
    int i=0;
    if(rhs!=NULL)
    {
        if(rhs->data !=NULL)
        {
            for(i=0;i<rhs->row;i++)
            {
                free(rhs->data[i]);
                rhs->data[i] =NULL;
            }
            free(rhs->data);
            rhs->data=0;
            rhs->row =0;
            rhs->col =0;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }
}

void initial_vector_double(vector_double* rhs,SetValue set)
{
    if(rhs->data ==0) return;
    if(rhs->lenght==0)return;
    int i=0;
    int del=0;
    switch(set.set)
    {
        case 0:
            for(i=0;i<rhs->lenght;i++)
                rhs->data[i] =(double)set.max;
        break;
        case 1:
            for(i=0;i<rhs->lenght;i++)
                rhs->data[i] =(double)(set.min+rand()%(int)(1+set.max-set.min));
        break;
        case 2:
            for(i=0;i<rhs->lenght;i++)
                rhs->data[i] =(double)set.max*((i)%2==0)+(double)set.min*(i%2==1);
        break;
        case 3:
            del = (double)((set.max-set.min)/(double)(rhs->lenght));
            set.set=2;
            if(del==0) initial_vector_double(rhs,set);
            else
            for(i=0;i<rhs->lenght;i++)
                rhs->data[i] =set.min+(i+1)*(del);
        break;
        case 4:
            for(i=0;i<rhs->lenght;i++)
                rhs->data[i] =(i==0)*1;
        break;
        default:
        break;
    }
}
void initial_matrix_double(matrix_double* rhs,SetValue set)
{
    if(rhs->data ==0) return;
    if(rhs->row==0 ||rhs->col==0)return;
    int i=0,j=0;
    char del=0;
    switch(set.set)
    {
        case 0:
            for(i=0;i<rhs->row;i++)
               for(j=0;j<rhs->col;j++)
                rhs->data[i][j] =(double)set.max;
        break;
        case 1:
            for(i=0;i<rhs->row;i++)
               for(j=0;j<rhs->col;j++)
                rhs->data[i][j] =(double)(set.min+rand()%(int)(1+set.max-set.min));
        break;
        case 2:
            for(i=0;i<rhs->row;i++)
               for(j=0;j<rhs->col;j++)
                rhs->data[i][j] =(double)set.max*((j+i)%2==0)+(double)set.min*((j+i)%2==1);
        break;
        case 3:
            del = (double)((set.max-set.min)/(double)(rhs->row*rhs->col));
            set.set=2;
            if(del==0) initial_matrix_double(rhs,set);
            else
            for(i=0;i<rhs->row;i++)
               for(j=0;j<rhs->col;j++)
                rhs->data[i][j] =set.min+(i+1)*rhs->col*(del)+del*(1+j);
        break;
        case 4:
            for(i=0;i<rhs->row;i++)
               for(j=0;j<rhs->col;j++)
                rhs->data[i][j] =(i==j)*1;
        break;
        default:
        break;

    }
}

int supervise_matrix_double(const matrix_double *rhs)
{
    if(rhs == NULL){ return  1;}
    if(rhs->data ==0 && (rhs->row !=0 || rhs->col !=0)){return 1;}  /*Null matrix */
    if((rhs->col ==0||rhs->row==0) && rhs->data != 0){return 2;} /*Construction isn't compelete.*/
    return 0; /*complete !!! */
}
int supervise_vector_double(const vector_double *rhs)
{
    if(rhs == NULL) return 1; /*Null matrix */
    if(rhs->data ==0 && rhs->lenght !=0) return 2;  /*Null matrix */
    if(rhs->lenght==0&& rhs->data !=0) return 3; /*Construction isn't compelete.*/
    return 0; /*complete !!! */
}
void print_vector_double(vector_double *rhs,int option)
{
    int i;
    switch(option)
    {
        case 3:
        case 0:
            printf("lenght:%d\n",rhs->lenght);
            for(i=0;i<rhs->lenght;i++)
             printf("%0.13f\n",rhs->data[i]);
            break;
        case 1:
            printf("lenght:%d\n",rhs->lenght);
            break;
        case 2:
            for(i=0;i<rhs->lenght;i++)
             printf("%0.13f\n",rhs->data[i]);
            break;
        case 4: 
            for(i=0;i<rhs->lenght;i++)
             printf("%0.13f ",rhs->data[i]);
            printf("\n");   
            break;
        case 5:
            printf("lenght:%d\n",rhs->lenght);
            for(i=0;i<rhs->lenght;i++)
             printf("%0.13f ",rhs->data[i]);
            printf("\n");
            break;
        case 6: /* print in vector form */
            printf("[ ");
            for(i=0;i<rhs->lenght;i++)
             printf("%0.3f ",rhs->data[i]); 
            printf(" ] ");
            break;
        default: break;
    }
            
}
void print_matrix_double(matrix_double *rhs,int option)
{
    int i,j;
    if(supervise_matrix_double(rhs) == 0)
    {
        switch(option)
        {
            case 3:
            case 0:
                printf("row:%d col:%d\n",rhs->row,rhs->col);
                for(i=0;i<rhs->row;i++)
                {
                 for(j=0;j<rhs->col;j++)
                    printf("%0.13f ",rhs->data[i][j]);
                 printf("\n");
                }
                break;
            case 1:
                printf("row:%d col:%d\n",rhs->row,rhs->col);
                break;
            case 2:
                for(i=0;i<rhs->row;i++)
                {
                 for(j=0;j<rhs->col;j++)
                    printf("%0.13f ",rhs->data[i][j]);
                 printf("\n");
                }
                break;
            case 4: 
                for(i=0;i<rhs->col;i++)
                {
                 for(j=0;j<rhs->row;j++)
                    printf("%0.13f ",rhs->data[j][i]);
                 printf("\n");
                }
                break;
            case 5:
                printf("row:%d col:%d\n",rhs->row,rhs->col);
                for(i=0;i<rhs->col;i++)
                {
                 for(j=0;j<rhs->row;j++)
                    printf("%0.13f ",rhs->data[j][i]);
                 printf("\n");
                }
                break;
            case 6:
                printf("row:%d col:%d\n",rhs->row,rhs->col);
                for(i=0;i<rhs->col;i++)
                {
                    for(j=0;j<rhs->row;j++)
                    {
                        printf("%0.4f ",rhs->data[j][i]);
                    }
                    printf("\n");
                }
            case 7:
                printf("row:%d col:%d\n",rhs->row,rhs->col);
                for(i=0;i<rhs->row;i++)
                {
                    for(j=0;j<rhs->col;j++)
                    {
                        printf("%0.4f ",rhs->data[i][j]);
                    }
                    printf("\n");
                }
                break;
            default: break;
        }
    }
    else
    {
        /* do nothing */
    }
}   
/*
void print_vector_char(vector_char *rhs,int option)
{
    int i;
    switch(option)
    {
        case 3:
        case 0:
            printf("lenght:%d\n",rhs->lenght);
            for(i=0;i<rhs->lenght;i++)
             printf("%d\n",rhs->data[i]);
            break;
        case 1:
            printf("lenght:%d\n",rhs->lenght);
            break;
        case 2:
            for(i=0;i<rhs->lenght;i++)
             printf("%d\n",rhs->data[i]);
            break;
        case 4: 
            for(i=0;i<rhs->lenght;i++)
             printf("%d ",rhs->data[i]);
            printf("\n");   
            break;
        case 5:
            printf("lenght:%d\n",rhs->lenght);
            for(i=0;i<rhs->lenght;i++)
             printf("%d ",rhs->data[i]);
            printf("\n");
            break;
        case 8:
            for(i=0;i<rhs->lenght;i++)
             printf("%c\n",rhs->data[i]);
            break;
        case 9: 
            for(i=0;i<rhs->lenght;i++)
             printf("%c ",rhs->data[i]);
            break;
        case 10:
            for(i=0;i<rhs->lenght;i++)
            printf("%d ",rhs->data[i]);
        default: break;
    }
            
}*/
/*
void print_matrix_char(matrix_char *rhs,int option)
{
    int i,j;
    switch(option)
    {
        case 3:
        case 0:
            printf("row:%d col:%d\n",rhs->row,rhs->col);
            for(i=0;i<rhs->row;i++)
            {
             for(j=0;j<rhs->col;j++)
                printf("%d ",rhs->data[i][j]);
             printf("\n");
            }
            break;
        case 1:
            printf("row:%d col:%d\n",rhs->row,rhs->col);
            break;
        case 2:
            for(i=0;i<rhs->row;i++)
            {
             for(j=0;j<rhs->col;j++)
                printf("%d ",rhs->data[i][j]);
             printf("\n");
            }
            break;
        case 4: 
            for(i=0;i<rhs->col;i++)
            {
             for(j=0;j<rhs->row;j++)
                printf("%d ",rhs->data[j][i]);
             printf("\n");
            }
            break;
        case 5:
            printf("row:%d col:%d\n",rhs->row,rhs->col);
            for(i=0;i<rhs->col;i++)
            {
             for(j=0;j<rhs->row;j++)
                printf("%d ",rhs->data[j][i]);
             printf("\n");
            }
            break;
        case 8:
            for(i=0;i<rhs->row;i++)
            {
             for(j=0;j<rhs->col;j++)
                printf("%c ",rhs->data[i][j]);
             printf("\n");
            }
            break;
        case 9:
            for(i=0;i<rhs->col;i++)
            {
             for(j=0;j<rhs->row;j++)
                printf("%c ",rhs->data[j][i]);
             printf("\n");
            }
        default: break;
    }
}   
*/
/* operation */
int multiply_v_m_double(vector_double *rhs,matrix_double *lhs,matrix_double *res)
{
    int i,j,factor =supervise_matrix_double(res);
    if(supervise_vector_double(rhs) || supervise_matrix_double(lhs))    
    {
        return 1;// failed 
    }
    if(lhs->row!=1)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
    
        *res =new_matrix_double(rhs->lenght,lhs->col);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != rhs->lenght || res->col !=lhs->col)
        {
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->lenght,lhs->col);
        }
    }

    for(i=0;i<rhs->lenght;i++)
    {
        for(j=0;j<lhs->col;j++)
           res->data[i][j]= rhs->data[i]*lhs->data[0][j];   
    }   

return 0;//complete
}
int multiply_vt_m_double(vector_double *rhs,matrix_double *lhs,matrix_double *res)
{
    int i,j,factor =supervise_matrix_double(res);
    SetValue set={0,0.0,0.0};
    if(supervise_vector_double(rhs) || supervise_matrix_double(lhs))    
    {
        return 1;// failed 
    }
    if(lhs->row!=rhs->lenght)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res=new_matrix_double(1,lhs->col);
        initial_matrix_double(res,set);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != 1 || res->col !=lhs->col)
        {   
            delete_matrix_double(res);
            *res=new_matrix_double(1,lhs->col);
            
        }
        initial_matrix_double(res,set);
    }

        for(i=0;i<lhs->col;i++)
         for(j=0;j<rhs->lenght;j++)
           res->data[0][i]+= rhs->data[j]*lhs->data[j][i];  

return 0;//complete
}
int multiply_v_mt_double(vector_double *rhs,matrix_double *lhs,matrix_double *res)
{
    int i,j,factor =supervise_matrix_double(res);
    if(supervise_vector_double(rhs) || supervise_matrix_double(lhs))    
    {
        return 1;// failed 
    }
    if(lhs->col!=1)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res=new_matrix_double(rhs->lenght,lhs->row);
        //initial_matrix_double(res,set);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != rhs->lenght || res->col !=lhs->row)
        {   
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->lenght,lhs->row);
            
        }
        //initial_matrix_double(res,set);
    }

        for(i=0;i<rhs->lenght;i++)
         for(j=0;j<lhs->row;j++)
           res->data[i][j]= rhs->data[i]*lhs->data[j][0];   

return 0;//complete
}
int multiply_m_v_double(matrix_double *rhs,vector_double *lhs,vector_double *res)
{
    int i,j,factor =supervise_vector_double(res);
    SetValue set={0,0.0,0.0};
    if(supervise_vector_double(lhs) || supervise_matrix_double(rhs))    
    {
        return 1;// failed 
    }
    if(lhs->lenght!=rhs->col)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res=new_vector_double(rhs->row);
        initial_vector_double(res,set);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->lenght != lhs->lenght)
        {   
            delete_vector_double(res);
            *res=new_vector_double(rhs->row);
            
        }
        initial_vector_double(res,set);
    }

        for(i=0;i<rhs->row;i++)
         for(j=0;j<lhs->lenght;j++)
           res->data[i]+= rhs->data[i][j]*lhs->data[j]; 

return 0;//complete
}
int multiply_mt_v_double(matrix_double *rhs,vector_double *lhs,vector_double *res)
{
    int i,j,factor =supervise_vector_double(res);
    SetValue set={0,0.0,0.0};
    if(supervise_vector_double(lhs) || supervise_matrix_double(rhs))    
    {
        return 1;// failed 
    }
    if(lhs->lenght!=rhs->row)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res=new_vector_double(rhs->col);
        initial_vector_double(res,set);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->lenght != lhs->lenght)
        {   
            delete_vector_double(res);
            *res=new_vector_double(rhs->col);
            
        }
        initial_vector_double(res,set);
    }

        for(i=0;i<rhs->col;i++)
         for(j=0;j<lhs->lenght;j++)
           res->data[i]+= rhs->data[j][i]*lhs->data[j]; 

return 0;//complete
}
int multiply_m_vt_double(matrix_double *rhs,vector_double *lhs,matrix_double *res)
{
    int i,j,factor =supervise_matrix_double(res);
    if(supervise_vector_double(lhs) || supervise_matrix_double(rhs))    
    {
        return 1;// failed 
    }
    if(factor==1)
    {
        *res=new_matrix_double(rhs->row,lhs->lenght);
    //  initial_matrix_double(res,set);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != rhs->row || res->col != lhs->lenght)
        {   
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->row,lhs->lenght);
            
        }
        //initial_matrix_double(res,set);
    }

        for(i=0;i<rhs->row;i++)
         for(j=0;j<lhs->lenght;j++)
            res->data[i][j]= rhs->data[i][0]*lhs->data[j];  

return 0;//complete
} 
int multiply_m_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
    int i,j,k,factor =supervise_matrix_double(res);
    SetValue set={0,0.0,0.0};
    if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))    
    {
        return 1;// failed 
    }
    if(lhs->row!=rhs->col)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res= new_matrix_double(rhs->row,lhs->col);
        initial_matrix_double(res,set);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != rhs->row || res->col != lhs->col)
        {   
            delete_matrix_double(res);
            *res= new_matrix_double(rhs->row,lhs->col);
            
        }
        initial_matrix_double(res,set);
    }

        for(i=0;i<rhs->row;i++)
         for(j=0;j<lhs->col;j++)
            for(k=0;k<rhs->col;k++)
            res->data[i][j]+= rhs->data[i][k]*lhs->data[k][j];  

return 0;//complete
}
int multiply_mt_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
    int i,j,k,factor =supervise_matrix_double(res);
    SetValue set={0,0.0,0.0};
    if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))    
    {
        return 1;// failed 
    }
    if(lhs->row!=rhs->row)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res=new_matrix_double(rhs->col,lhs->col);
        initial_matrix_double(res,set);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != rhs->col || res->col != lhs->col)
        {   
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->col,lhs->col);
            
        }
        initial_matrix_double(res,set);
    }

        for(i=0;i<rhs->col;i++)
         for(j=0;j<lhs->col;j++)
            for(k=0;k<rhs->row;k++)
            res->data[i][j]+= rhs->data[k][i]*lhs->data[k][j];  

return 0;//complete
}
int multiply_m_mt_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
    int i,j,k,factor =supervise_matrix_double(res);
    SetValue set={0,0.0,0.0};
    if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))    
    {
        return 1;// failed 
    }
    if(lhs->col!=rhs->col)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res= new_matrix_double(rhs->row,lhs->row);
        initial_matrix_double(res,set);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != rhs->col || res->col != lhs->col)
        {   
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->row,lhs->row);
    
        }
        initial_matrix_double(res,set);
    }

        for(i=0;i<rhs->row;i++)
         for(j=0;j<lhs->row;j++)
            for(k=0;k<rhs->col;k++)
            res->data[i][j]+= rhs->data[i][k]*lhs->data[j][k];  

return 0;//complete
}
int multiply_v_vt_double(vector_double *rhs,vector_double *lhs,matrix_double *res)
{
    int i,j,factor =supervise_matrix_double(res);
    SetValue set={0,0.0,0.0};
    if(supervise_vector_double(lhs) || supervise_vector_double(rhs))    
    {
        return 1;// failed 
    }
    if(factor==1)
    {
        *res=new_matrix_double(rhs->lenght,lhs->lenght);
        initial_matrix_double(res,set);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != rhs->lenght || res->col != lhs->lenght)
        {   
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->lenght,lhs->lenght);
            
        }
        initial_matrix_double(res,set);
    }

        for(i=0;i<rhs->lenght;i++)
         for(j=0;j<lhs->lenght;j++)
            res->data[i][j]= rhs->data[i]*lhs->data[j]; 

return 0;//complete
}
int multiply_vt_v_double(const vector_double *rhs,const vector_double *lhs,double *res)//dot product
{
    int i,factor =(res==0);
    if(supervise_vector_double(lhs) || supervise_vector_double(rhs))    
    {
        return 1;// failed 
    }
    if(rhs->lenght != lhs->lenght)
    {
        return 2; // size failed
    }
    if(factor==1)
    {
        return 2; // res is null
    }
        *res =0;
        for(i=0;i<rhs->lenght;i++)
            *res+= rhs->data[i]*lhs->data[i];   

return 0;//complete
}
int dotmultiply_v_double(vector_double *rhs,vector_double *lhs,vector_double *res)
{
    int i,factor =supervise_vector_double(res);
    if(supervise_vector_double(lhs) || supervise_vector_double(rhs))    
    {
        return 1;// failed 
    }
    if(lhs->lenght!=rhs->lenght)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res= new_vector_double(rhs->lenght);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->lenght != rhs->lenght)
        {   
            delete_vector_double(res);
            *res=new_vector_double(rhs->lenght);
    
        }
    }

         for(i=0;i<rhs->lenght;i++)
            res->data[i]= rhs->data[i]*lhs->data[i];    

return 0;//complete
}
int dotmultiply_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
    int i,j,factor =supervise_matrix_double(res);
    if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))    
    {
        return 1;// failed 
    }
    if(lhs->col!=rhs->col || rhs->row != lhs->row)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res= new_matrix_double(rhs->row,rhs->col);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != rhs->row || res->col != lhs->col)
        {   
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->row,lhs->col);
    
        }
    }

        for(i=0;i<rhs->row;i++)
         for(j=0;j<lhs->col;j++)
            res->data[i][j]= rhs->data[i][j]*lhs->data[i][j];   

return 0;//complete
}
int scalarmultiply_v_double(vector_double *rhs,double *lhs,vector_double *res)
{
    int i,factor =supervise_vector_double(res);
    if(lhs==0 || supervise_vector_double(rhs))  
    {
        return 1;// failed 
    }
    if(factor==1)
    {
        *res= new_vector_double(rhs->lenght);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->lenght != rhs->lenght)
        {   
            delete_vector_double(res);
            *res=new_vector_double(rhs->lenght);
    
        }
    }

         for(i=0;i<rhs->lenght;i++)
            res->data[i]= rhs->data[i]*(*lhs);  

return 0;//complete
}
int scalarmultiply_m_double(matrix_double *rhs,double *lhs,matrix_double *res)
{
    int i,j,factor =supervise_matrix_double(res);
    if(lhs==0 || supervise_matrix_double(rhs))  
    {
        return 1;// failed 
    }
    if(factor==1)
    {
        *res= new_matrix_double(rhs->row,rhs->col);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->row != rhs->row || res->col != rhs->col)
        {   
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->row,rhs->col);
    
        }
    }

        for(i=0;i<rhs->row;i++)
         for(j=0;j<rhs->col;j++)
            res->data[i][j]= rhs->data[i][j]*(*lhs);    

return 0;//complete
} 
int plus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res)
{
    int i,factor =supervise_vector_double(res);
    if(supervise_vector_double(lhs) || supervise_vector_double(rhs))    
    {
        return 1;// failed 
    }
    if(lhs->lenght!=rhs->lenght)
    {
        return 2; //failed size
    }
    if(factor==1)
    {
        *res= new_vector_double(rhs->lenght);
    }
    else if(factor==2) 
    {
        return 3; // failed to get result
    }
    else if(factor==0)
    {
        if(res->lenght != rhs->lenght)
        {   
            delete_vector_double(res);
            *res=new_vector_double(rhs->lenght);
    
        }
    }

         for(i=0;i<rhs->lenght;i++)
            res->data[i]= rhs->data[i]+lhs->data[i];

return 0;/* complete */
}
int plus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
    int i,j,factor =supervise_matrix_double(res);
    if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))
    {
        return 1;/* failed */
    }
    if(lhs->col!=rhs->col || rhs->row != lhs->row)
    {
        return 2; /*failed size */
    }
    if(factor==1)
    {
        *res= new_matrix_double(rhs->row,rhs->col);
    }
    else if(factor==2) 
    {
        return 3; /* failed to get result */
    }
    else if(factor==0)
    {
        if(res->row != rhs->row || res->col != lhs->col)
        {
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->row,lhs->col);

        }
        else
        {
            /* do nothing */
        }
    }

    for(i=0;i<rhs->row;i++)
    {
        for(j=0;j<lhs->col;j++)
        {
            res->data[i][j]= rhs->data[i][j]+lhs->data[i][j];
        }
    }
    return 0;/*complete */
}
int minus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res)
{
    int i,factor =supervise_vector_double(res);
    if(supervise_vector_double(lhs) || supervise_vector_double(rhs))
    {
        return 1;/* failed */
    }
    if(lhs->lenght!=rhs->lenght)
    {
        return 2; /* failed size */
    }
    if(factor==1)
    {
        *res= new_vector_double(rhs->lenght);
    }
    else if(factor==2) 
    {
        return 3; /* failed to get result */
    }
    else if(factor==0)
    {
        if(res->lenght != rhs->lenght)
        {
            delete_vector_double(res);
            *res=new_vector_double(rhs->lenght);

        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }
    for(i=0;i<rhs->lenght;i++)
    {
        res->data[i]= rhs->data[i]-lhs->data[i];
    }
    return 0;/* complete */
}
int minus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
    int i,j,factor =supervise_matrix_double(res);
    if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))
    {
        return 1;/* failed */
    }
    if(lhs->col!=rhs->col || rhs->row != lhs->row)
    {
        return 2; /* failed size */
    }
    if(factor==1)
    {
        *res= new_matrix_double(rhs->row,rhs->col);
    }
    else if(factor==2) 
    {
        return 3; /* failed to get result */
    }
    else if(factor==0)
    {
        if(res->row != rhs->row || res->col != lhs->col)
        {
            delete_matrix_double(res);
            *res=new_matrix_double(rhs->row,lhs->col);
        }
    }

    for(i=0;i<rhs->row;i++)
    {
        for(j=0;j<lhs->col;j++)
        {
            res->data[i][j]= rhs->data[i][j]-lhs->data[i][j];
        }
    }
    return 0;/* complete */
}
void copy_v_double(vector_double *rhs,vector_double *lhs)
{
    if(rhs != lhs)
    {
        int index1 = 0;
        int num = lhs->lenght;
        delete_vector_double(rhs);
        *rhs = new_vector_double(num);
        for(index1 =0 ;index1<num;index1++)
        {
            rhs->data[index1] = lhs->data[index1];
        }
    }
    else
    {
        /* do nothing */
    }
}/* end scope copy_v_double*/
void copy_m_double(matrix_double *rhs,matrix_double *lhs)
{
    if(rhs != lhs)
    {
        int index1 = 0;
        int index2 = 0;
        int row = lhs->row;
        int col    = lhs->col;
        delete_matrix_double(rhs);
        *rhs = new_matrix_double(row,col);
        for(index1 =0 ;index1<row;index1++)
        {
            for(index2 =0;index2<col;index2++)
            {
                rhs->data[index1][index2] = lhs->data[index1][index2];
            }
        }
    }
}/*end scope copy_m_double*/
void swap_v_double(vector_double *rhs,vector_double *lhs)
{
    vector_double dummy= new_vector_double(0);
    copy_v_double(&dummy,rhs);
    copy_v_double(rhs,lhs);
    copy_v_double(lhs,&dummy);
    delete_vector_double(&dummy);
}/*  end scope swap_v_double*/
void swap_m_double(matrix_double *rhs,matrix_double *lhs)
{
    matrix_double dummy= new_matrix_double(0,0);
    copy_m_double(&dummy,rhs);
    copy_m_double(rhs,lhs);
    copy_m_double(lhs,&dummy);
    delete_matrix_double(&dummy);
}/* end scope swap_m_double*/
void minorMdouble(matrix_double *rhs,int row,int col)
{
    matrix_double dummy= new_matrix_double(0,0);
    int index,index2,index3=0,index4=0;
    int nCol = rhs->col;
    int nRow = rhs->row;
    if(rhs == NULL || row <0 || col <0)
    {
        return;
    } /* end if(rhs == NULL || row <0 || col <0)*/
    else
    {
        /* do nothing */
    } /*end else */
    dummy = new_matrix_double(rhs->row-1,rhs->col-1);
    for(index =0 ;index<nRow;index++)
    {
        if(index ==row)
        {
            continue;
        }
        else
        {
            /* do nothing */
        }
        index4 =0;
        for(index2 =0;index2<nCol;index2++)
        {
            if(index2 == col)
            {
                continue;
            }
            else
            {
                /* do nothing */
            }
            dummy.data[index3][index4++] = rhs->data[index][index2];
        }
        index3++;
    }
    delete_matrix_double(rhs);
    *rhs = dummy;
}/* end minorMdouble(matrix_double *rhs,int row,int col) */

matrix_double concatColMatrix(matrix_double *rhs,matrix_double *lhs)
{
    int fact1 = 1;
    int num = 0;
    int num2 = 0;
    int index = 0;
    int index2 = 0;
    matrix_double ret = new_matrix_double(0,0);
    if((rhs!=NULL)&&(lhs!=NULL))
    {
        fact1 = (rhs->row == lhs->row);
    }
    else
    {
        fact1 = 0;
    }
    if(fact1 == 1)
    {
        ret = new_matrix_double(rhs->row,rhs->col+lhs->col);
        num = rhs->row;
        num2 = rhs->col;
        for(index = 0;index < num;index++)
        {
            for(index2=0;index2 < num2;index2++)
            {
                ret.data[index][index2] = rhs->data[index][index2];
            }
        }
        for(index = 0;index < num;index++)
        {
            for(index2=0;index2 < num2;index2++)
            {
                ret.data[index][index2+rhs->col] = lhs->data[index][index2];
            }
        }
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

void rowOperationM(matrix_double *rhs,matrix_double *ret,unsigned int r1,double fact1,unsigned int r2,double fact2,unsigned int rowRet)
{
    int index = 0;
    int num = 0;
    if((rhs != NULL)&&(ret != NULL))
    {
        num = ret->col;
        /*printf("rowRet :%u, r1:%u r2:%u\n",rowRet,r1,r2);*/
        if((r1 < rhs->row)&&(r2<rhs->row)&&(rowRet<rhs->row))
        {
            if((fact1 != 0)&&(fact2 != 0))
            {
                for(index=0;index <num;index++)
                {
                    ret->data[rowRet][index] = fact1*rhs->data[r1][index] + fact2*rhs->data[r2][index];
                }
            }
            else if((fact1 == 0)&&(fact2 != 0))
            {
                for(index=0;index <num;index++)
                {
                    ret->data[rowRet][index] = fact2*rhs->data[r2][index];
                }
            }
            else if((fact1 != 0)&&(fact2 == 0))
            {
                
       /* printf("---------------rowRet :%u, r1:%u r2:%u\n",rowRet,r1,r2);*/
                for(index=0;index <num;index++)
                {
                    ret->data[rowRet][index] = fact1*rhs->data[r1][index];
                   /* printf("%f ",ret->data[rowRet][index]);*/
                }
               /* printf(" -- %p \n",ret->data);*/
            }
            else
            {
                for(index=0;index <num;index++)
                {
                    ret->data[rowRet][index] = 0;
                }
            }

        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }
}
/*
opt = 0 --> diagonal matrix
opt = 1 --> upper triangular matrix
opt = 2 --> lower triangular matrix
*/
int GaussElimination(matrix_double *rhs,matrix_double *retm,const int numRowVars,int opt)
{
    int initVal =0;
    int index =0;
    int index2 =0;
    int pivot = 0;
    int num =0;
    int num2 =0;
    int temp = numRowVars;
    matrix_double *lhs = NULL;
    int ret2 = 1;
    int ret = supervise_matrix_double(rhs);
    ret += supervise_matrix_double(retm);
    ret = (ret==0) &&(numRowVars >= 1);
    if(ret ==1 )
    {
        ret = (numRowVars <= rhs->col);
        ret = (ret == 1)&&(rhs->col == retm->col)&&(rhs->row == retm->row);
    }
    else
    {
        /* do nothing */
    }
    if(ret ==1)
    {
        lhs = rhs;
        pivot = 0;
        if(numRowVars >= rhs->row)
        {
            num = rhs->row;
            num2 = rhs->row;
        }
        else
        {
            num = rhs->row;
            num2 = numRowVars;
        }
        if((opt == 0) ||(opt == 1))
        {
            for(index=0;index < num2;index++) // for(index=num2-1;index >-1;index--)
            {
                if(lhs->data[pivot][index] != 0) // if(lhs->data[index][index] != 0)
                {
                    if(opt == 0) /* 0 --> diagonal matrix */
                    {
                        initVal = 0;
                    }
                    else if(opt == 1)/* opt = 1 --> upper triangular matrix */
                    {
                        initVal = index;
                    }
                    for(index2 = initVal ;index2 <num;index2++) //for(index2 = num-1 ;index2 >-1;index2--)
                    {
                        if((index2 != pivot)&&((index==0)||(lhs->data[index2][index]!=0.0)))
                        {
                            rowOperationM(lhs,retm,index2,1.0,pivot,-1*lhs->data[index2][index]/lhs->data[pivot][index],index2);
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    if(index == 0)
                    {
                        rowOperationM(lhs,retm,pivot,1.0,0,0.0,pivot);
                        lhs =retm;
                    }
                    else
                    {
                        /* do nothing */
                    }
                    if(index != pivot)
                    {
                        swapRowMdouble(retm,pivot,index);
                        rowOperationM(lhs,retm,pivot,-1.0,0,0.0,pivot);
                        pivot = index;
                    }
                    else
                    {
                        /* do nothing */
                    }
                    pivot++;
                }
                else
                {
                    /* swap */
                    ret2 = 0;
                    for(index2=index;index2<num;index2++)
                    {
                        if(lhs->data[index2][index]!= 0)
                        {
                            pivot = index2;
                            index2 = num;
                            ret2 = 1;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    if(ret2 == 0)
                    {
                        index = num2;
                    }
                    else
                    {
                        index--;
                    }
                } 
            }
        } 
        else if(opt == 2) /* opt = 2 --> lower triangular matrix */
        {
            for(index=num2-1;index >-1;index--)
            {
                if(lhs->data[index][index] != 0)
                {
                    for(index2 = num-1 ;index2 >-1;index2--)
                    {
                        if((index2 != index)&&((index==0)||(lhs->data[index2][index]!=0.0)))
                        {
                            rowOperationM(lhs,retm,index2,1.0,index,-1*lhs->data[index2][index]/lhs->data[index][index],index2);
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    if(index == 0)
                    {
                        rowOperationM(lhs,retm,0,1.0,0,0.0,0);
                        lhs =retm;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                else
                {
                    /* do nothing */
                }

            }
        }
        if(ret2 == 1)
        {
            /* check many solution or impossible solution*/
            num2 = rhs->row;
            num = rhs->col;
            for(index=0;index<num2;index++)
            {
                if(retm->data[index][0] == 0.0)
                {
                    temp = numRowVars-1;
                    for(index2 = 1;index2<num;index2++)
                    {
                        if(retm->data[index][index2]== 0.0)
                        {
                            temp--;
                        }
                        else
                        {
                            index2 = num;
                            temp = numRowVars-1;
                            
                        }

                    }
                    if(temp == 0)
                    {
                        index = num2;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                else
                {
                    /* do nothing */
                }
            }
            if(temp <=0)
            {
                ret = 1;
            }
            else
            {
                ret = 0;
            }
        }
        else
        {
            ret = 1;
        }
    }
    else
    {
        printf("cannot do GaussElimination : %d, file:%s  \n",__LINE__,__FILE__);
    }
    return ret;
}
void cutRowMdouble(matrix_double *rhs,int row)
{
    if(rhs == NULL || row < 0)
    {
        return;
    } // end if(rhs == NULL || row < 0)
    else
    {
        //do nothing 
    } // end
    matrix_double dummy = new_matrix_double(rhs->row-1,rhs->col);
    int index,index2,index3=0;
    int numRow = rhs->row;
    int numCol = rhs->col;
    for(index=0;index<numRow;index++)
    {
        if(row == index)
        {
            continue;
        }//end  if(row == index)
        else
        {
            // do nothing
        }//end else if(row == index)
        for(index2 = 0;index2<numCol;index2++)
        {
            dummy.data[index3][index2] = rhs->data[index][index2];
        } // end for(index2 = 0;index2<numCol;index2++)
        index3++;
    }
    delete_matrix_double(rhs);
    *rhs = dummy;
} //end cutRowMdouble(matrix_double *rhs,int row)
void swapRowMdouble(matrix_double *rhs,int row1,int row2)
{
    if(rhs == NULL)
    {
        return;
    }
    else
    {
        //do nothing
    }
    if(rhs->row <= row1 || rhs->row <= row2)
    {
        return;
    }
    else
    {
        //do nothing
    }
    double dummy;
    int index =0;
    int num = rhs->col;
    for(index = 0;index<num;index++)
    {
        dummy = rhs->data[row1][index];
        rhs->data[row1][index] = rhs->data[row2][index];
        rhs->data[row2][index] = dummy;
    }
}// end swapRowMdouble
int compareEqual_v_double(vector_double *rhs,vector_double *lhs)
{
    int index =0;
    int ret = 0;
    int numLoop =0;
    if(rhs->lenght > lhs->lenght)
    {
        numLoop = lhs->lenght;
    }
    else if(rhs->lenght < lhs->lenght)
    {
        numLoop = rhs->lenght;
    }
    else
    {
        numLoop = rhs->lenght;
        ret = 1;
    }
    for(index =0 ;index<numLoop;index++)
    {
        if(rhs->data[index] > lhs->data[index])
        {
            ret = 2;
        }
        else if(rhs->data[index] < lhs->data[index])
        {
            ret = -1;
        }
    }
    return ret;
}//end compareEqual_v_double
int compareEqual_m_double(matrix_double *rhs,matrix_double *lhs)
{
    int index  = 0;
    int index2 = 0;
    if(rhs->row != lhs->row || rhs->col != lhs->col)
    {
        return 0;
    }
    for(index =0 ;index<rhs->row;index++)
    {
        for(index2 =0;index2<rhs->col;index2++)
        {
            if(rhs->data[index][index2] != lhs->data[index][index2])
            {
                return 0;
            }
        }
    }
    return 1;
}//end compareEqual_m_double
vector_double       rowMatrix2Vectordouble(matrix_double *rhs,int index)
{
    int index2      =0;
    int col1        =0;
    vector_double dummy = new_vector_double(0);
    if(rhs == NULL || index <0)
    {
        return dummy;
    } //end if(rhs == NULL)
    else
    {
        col1 = rhs->col;
        dummy = new_vector_double(rhs->col);
        for(index2 =0 ;index2 < col1;index2++)
        {
            dummy.data[index2] = rhs->data[index][index2];
        }
    } // end else
    return dummy;
} // end rowMatrix2Vectordouble
double determinant(matrix_double *a)
{
    double det=0;
    int index =0 ,index2=0,index0=0,index3=0;
    
    matrix_double b = new_matrix_double(0,0);
    if(a->row <1)
    {
        return  det;
    }
    else if(a->row ==1)
    {
        return a->data[0][0];
    }
    else if(a->row ==2)
    {
        return (a->data[0][0]*a->data[1][1])-(a->data[0][1]*a->data[1][0]);
    }
    else
    {
       b = new_matrix_double(a->row-1,a->row-1);
       for(index0 = 0 ;index0 < a->row;index0++)
       {
        
        index3 =0 ;
        for(index = 0;index <a->row;index++)
        {
           if(index0 == index)
           {
            continue;
           }
           else
           {
            //do nothing
           }    
           for(index2 =1;index2 <a->row;index2++)
           {
            b.data[index3][index2-1] =a->data[index][index2];
           }
           index3++;
        }
        det += (((index0%2)==0)?1.0:-1.0)*a->data[index0][0]*determinant(&b);
        }

    }
    delete_matrix_double(&b);
    return det;
}
double determinant2(matrix_double *a,matrix_double *buff)
{
    double temp = 1;
    int index =0;
    int num =0;
    if((a!=NULL)&&(buff!=NULL))
    {
        if((a->row == a->col)&&(buff->row == a->col)&&(buff->col ==a->row))
        {
            num = a->row;
            if(GaussElimination(a,buff,a->row,1) == 0)
            {
                for(index = 0;index <num;index++)
                {
                    temp = temp*buff->data[index][index];
                }
            }
            else
            {
                temp = 0;
            }
            
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }
    return temp;
}
void colFactorMatrix(matrix_double *a,matrix_double *c)
{
    int index,index2,index3,index4,index5,index6;
    double det;
    matrix_double b = new_matrix_double(0,0);
    b = new_matrix_double(a->row-1,a->row-1);
    for(index =0;index < a->row;index++)
    {
      for(index2=0;index2<a->col;index2++)
      {
        index5 = 0;
        for(index3=0;index3<a->row;index3++)
        {
            if(index3==index2)
            {
                continue;
            }
            else
            {
                //do noting
            }
            index6 = 0;
            for(index4=0;index4<a->col;index4++)
            {
                if(index4==index)
                {
                continue;
                }
                else
                    {
                //do nothing        
                }
                b.data[index5][index6] = a->data[index3][index4];
                index6++;
            }
            index5++;
        }
        det = determinant(&b);
        c->data[index][index2]  = det*((index+index2)%2==1?-1:1);
        
      }
    }
    delete_matrix_double(&b);

}
void matrixInverse(matrix_double *a,matrix_double *c)
{
    double detInverse = 1.0/determinant2(a,c);
    colFactorMatrix(a,c);
    scalarmultiply_m_double(c,&detInverse,c); 
}
void matrixInverse2(matrix_double *a,matrix_double *c)
{
    matrix_double tempM = new_matrix_double(0,0);
    SetValue setRang = {4,1,1};
    
    int index =0;
    int index2 =0;
    int pivot = 0;
    int num =0;
    int num2 =0;
    matrix_double *lhs = NULL;
    matrix_double *rhs = NULL;
    int ret2 = 1;
    double temp = 0;
    int ret = supervise_matrix_double(a);
    ret += supervise_matrix_double(c);
    if(ret ==0)
    {
        rhs = a;
        lhs = rhs;
        tempM = new_matrix_double(rhs->row,rhs->col);
        pivot = 0;
        num = rhs->row;
        num2 = rhs->row;
        initial_matrix_double(c,setRang);
        initial_matrix_double(&tempM,setRang);
        for(index=0;index < num2;index++) // for(index=num2-1;index >-1;index--)
        {
       /* printf("round :%d ---------------------------\n",index+1);*/
            if(lhs->data[pivot][index] != 0) // if(lhs->data[index][index] != 0)
            {
                for(index2 = 0 ;index2 <num;index2++) //for(index2 = num-1 ;index2 >-1;index2--)
                {
                    if((index2 != pivot)&&((index==0)||(lhs->data[index2][index]!=0.0)))
                    {
                        temp = -1.0*lhs->data[index2][index]/lhs->data[pivot][index];
                        rowOperationM(lhs,&tempM,index2,1.0,pivot,temp,index2);
                        rowOperationM(c,c,index2,1.0,pivot,temp,index2);
                       /* printf(" matrix 1 ====================\n");
                        print_matrix_double(&tempM,7);
                        
                        printf("inverse ----------------------------\n");
                        print_matrix_double(c,7);
                   */
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                if(index == 0)
                {
                    rowOperationM(lhs,&tempM,pivot,1.0,0,0.0,pivot);
                    lhs =&tempM;
                }
                else
                {
                    /* do nothing */
                }
                if(index != pivot)
                {
                    swapRowMdouble(&tempM,pivot,index);
                    swapRowMdouble(c,pivot,index);
                    rowOperationM(lhs,&tempM,pivot,-1.0,0,0.0,pivot);
                    rowOperationM(c,c,pivot,-1.0,0,0.0,pivot);
                   /* 
                    print_matrix_double(&tempM,7);
                        printf("inverse 222----------------------------\n");
                    print_matrix_double(c,7);
                    */pivot = index;
                }
                else
                {
                    /* do nothing */
                }
                /*
                if(tempM.data[index][index] != 0)
                {   
                    rowOperationM(c,c,pivot,1.0/tempM.data[index][index],0,0.0,pivot);
                }
                else
                {   index = num2;
                    printf("Cannot determine inverse matrix \n");
                }*/
                pivot++;
            }
            else
            {
                /* swap */
                ret2 = 0;
                for(index2=index;index2<num;index2++)
                {
                    if(lhs->data[index2][index]!= 0)
                    {
                        pivot = index2;
                        index2 = num;
                        ret2 = 1;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                if(ret2 == 0)
                {
                    index = num2;
                }
                else
                {
                    index--;
                }
            } 
        }
        if(ret2 != 0)
        {
            for(index=0;index<num;index++)
            {
                temp = tempM.data[index][index];
                if(temp != 0)
                {
                    for(index2=0;index2<num2;index2++)
                    {
                        c->data[index][index2] = c->data[index][index2]/temp;
                    }
                }
                else
                {
                    index = num;
                    printf("Cannot determine inverse matrix \n");
                }
            }
        }
        /*print_matrix_double(&tempM,7);*/
    delete_matrix_double(&tempM);
    }
}
/* safe input of vector*/
/*
st = set
sf = safe
dg = debug
df = default
*/
/*debug mode */
double gtsfdg(vector_double *rhs,int index,int line,const char *filename)
{
    double ret=0.0;
    if(rhs==NULL)
    {
        printf("vector is Null at Ln:%d fl:%s\n",line,filename);
    }
    else if((rhs->lenght <=(unsigned int)index)||(index<0))
    {
        printf("index is out of range(%u) index:%dat Ln:%d fl:%s\n",rhs->lenght,index,line,filename);
    }
    else
    {
        ret =rhs->data[index];
    }
    return ret;
}
int stsfdg(vector_double *rhs,int index,double val,int line,const char *filename)
{
    int ret=0;
    if(rhs==NULL)
    {
        printf("vector is Null at Ln:%d fl:%s\n",line,filename);
    }
    else if((rhs->lenght <=(unsigned int)index)||(index<0))
    {
        printf("index is out of range(%u) index:%dat Ln:%d fl:%s\n",rhs->lenght,index,line,filename);
    }
    else
    {
        rhs->data[index] = val;
        ret=1;
    }
    return ret;
}
int stsfdfdg(vector_double *rhs,int index,double val,int line,const char *filename)
{
    int ret=0;
    if(rhs==NULL)
    {
        printf("vector is Null at Ln:%d fl:%s\n",line,filename);
    }
    else if((rhs->lenght <=(unsigned int)index)||(index<0))
    {
        printf("index is out of range(%u) index:%dat Ln:%d fl:%s\n",rhs->lenght,index,line,filename);
        if(index<0)
        {
            index=0;
        }
        else if(rhs->lenght <=(unsigned int)index)
        {
            index = rhs->lenght-1;
        }
        else
        {
            /* do nothing */
        }
        rhs->data[index] = val;
    }
    else
    {
        rhs->data[index] = val;
        ret=1;
    }
    return ret;
}
/* release mode*/
void stsf(vector_double *rhs,int index,double val)
{
    if(rhs==NULL)
    {
        /* do nothing */
    }
    else if((rhs->lenght <=(unsigned int)index)||(index<0))
    {
        /* do nothing */
    }
    else
    {
        rhs->data[index] = val;
    }
}
void stsfdf(vector_double *rhs,int index,double val)
{
    if(rhs==NULL)
    {
        /* do nothing */
    }
    else if((rhs->lenght <=(unsigned int)index)||(index<0))
    {
        if(index<0)
        {
            index=0;
        }
        else if(rhs->lenght <=(unsigned int)index)
        {
            index = rhs->lenght-1;
        }
        else
        {
            /* do nothing */
        }
        rhs->data[index] = val;
    }
    else
    {
        rhs->data[index] = val;
    }
}
