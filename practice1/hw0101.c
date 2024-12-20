#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct _polynomial
{
    char *name;
    int32_t *power;
    double *coefficient;
    int32_t num_terms;
};

void printpolynomials(struct _polynomial *polynomials, int32_t num_polynomials);
void printcoefficient(int32_t x, struct _polynomial polynomial);
void addelement(struct _polynomial *polynomial);
void removeelement(struct _polynomial *polynomial);
void printcoefficients(struct _polynomial *polynomials, int32_t num_polynomials);


void add_polynomials(struct _polynomial *p1, struct _polynomial *p2);
void subtract_polynomials(struct _polynomial *p1, struct _polynomial *p2);
void multiply_polynomials(struct _polynomial *p1, struct _polynomial *p2);
void divide_polynomials(struct _polynomial *p1, struct _polynomial *p2);

int main()
{
    int32_t choice=0;
    int32_t num_polynomial=0;
    struct _polynomial *polynomials = NULL;
    int32_t term=0;

    while(1)
    {
        printf("Please enter the number what you want to do?\n");
        printf(" -----------------------------------\n");
        printf("|(0)Exit                            |\n");
        printf("|(1)Print all polynomials           |\n");
        printf("|(2)Creat new polynomial            |\n");
        printf("|(3)Add element to polynomial       |\n");
        printf("|(4)Remove element from polynomial  |\n");
        printf("|(5)Print coefficients              |\n");
        printf("|(6)Add Polynomial                  |\n");
        printf("|(7)Subtract Polynomials            |\n");
        printf("|(8)Multiply Polynomials            |\n");
        printf("|(9)Divide Polynomials              |\n");
        printf(" -----------------------------------\n");
        printf("    Your choice: ");
        scanf("%d", &choice);
        
        if(choice == 0)
        {
            break;
        }
        else if(choice == 1)
        {
            printpolynomials(polynomials, num_polynomial);
        }
        else if(choice == 2)
        {
            num_polynomial++;
            polynomials = realloc(polynomials, num_polynomial * sizeof(struct _polynomial));

            polynomials[num_polynomial - 1].name = malloc(50);
            printf("Enter the name for the new polynomial: ");
            scanf("%s", polynomials[num_polynomial - 1].name);

            printf("Enter the number of terms in the polynomial: ");
            scanf("%d", &polynomials[num_polynomial - 1].num_terms);

            polynomials[num_polynomial - 1].power = malloc(polynomials[num_polynomial - 1].num_terms * sizeof(int32_t));
            polynomials[num_polynomial - 1].coefficient = malloc(polynomials[num_polynomial - 1].num_terms * sizeof(double));

            for (int32_t i = 0; i < polynomials[num_polynomial - 1].num_terms; i++)
            {
                printf("Enter coefficient for term %d: ", i + 1);
                scanf("%lf", &polynomials[num_polynomial - 1].coefficient[i]);
                printf("Enter power for term %d: ", i + 1);
                scanf("%d", &polynomials[num_polynomial - 1].power[i]);
            }
            
            for(int32_t i=0; i<polynomials[num_polynomial - 1].num_terms; i++)
            {
                for(int32_t j=i; j<polynomials[num_polynomial-1].num_terms; j++)
                {
                    if(polynomials[num_polynomial-1].power[i] < polynomials[num_polynomial-1].power[j])
                    {
                        int32_t temp = polynomials[num_polynomial-1].power[i];
                        polynomials[num_polynomial-1].power[i] = polynomials[num_polynomial-1].power[j];
                        polynomials[num_polynomial-1].power[j] = temp;
                        temp = polynomials[num_polynomial-1].coefficient[i];
                        polynomials[num_polynomial-1].coefficient[i] = polynomials[num_polynomial-1].coefficient[j];
                        polynomials[num_polynomial-1].coefficient[j] = temp;
                    }
                }
            }
        }
        else if (choice == 3)
        {
            if (num_polynomial == 0)
            {
                printf("No polynomial to add element to. Please create a polynomial first.\n");
                continue;
            }

            printf("Select a polynomial to add an element to (1-%d): ", num_polynomial);
            int32_t poly_index;
            scanf("%d", &poly_index);

            if (poly_index < 1 || poly_index > num_polynomial)
            {
                printf("Invalid polynomial selection.\n");
                continue;
            }

            addelement(&polynomials[poly_index - 1]);
        }
        else if (choice == 4)
        {
            if (num_polynomial == 0)
            {
                printf("No polynomial to remove element from. Please create a polynomial first.\n");
                continue;
            }

            printf("Select a polynomial to remove an element from (1-%d): ", num_polynomial);
            int32_t poly_index;
            scanf("%d", &poly_index);

            if (poly_index < 1 || poly_index > num_polynomial)
            {
                printf("Invalid polynomial selection.\n");
                continue;
            }

            removeelement(&polynomials[poly_index - 1]);
        }
        else if (choice == 5)
        {
            if (num_polynomial == 0)
            {
                printf("No polynomial to print coefficients. Please create a polynomial first.\n");
                continue;
            }

            printcoefficients(polynomials, num_polynomial);
        }
        else if (choice == 6)
        {
            printf("Which two polynomial you want to add(1-%d)", num_polynomial);
            int32_t poly_index1, poly_index2;
            scanf("%d %d", &poly_index1, &poly_index2);

            if (poly_index1 < 1 || poly_index1 > num_polynomial || poly_index2 < 1 || poly_index2 > num_polynomial)
            {
                printf("Invalid polynomial selection.\n");
                continue;
            }

            add_polynomials(&polynomials[poly_index1 - 1], &polynomials[poly_index2 - 1]);
        }
        else if (choice == 7)
        {
            printf("Which two polynomial you want to subtract(1-%d)", num_polynomial);
            int32_t poly_index1, poly_index2;
            scanf("%d %d", &poly_index1, &poly_index2);

            if (poly_index1 < 1 || poly_index1 > num_polynomial || poly_index2 < 1 || poly_index2 > num_polynomial)
            {
                printf("Invalid polynomial selection.\n");
                continue;
            }

            subtract_polynomials(&polynomials[poly_index1 - 1], &polynomials[poly_index2 - 1]);
        }
        else if (choice == 8)
        {
            printf("Which two polynomial you want to multiply(1-%d)", num_polynomial);
            int32_t poly_index1, poly_index2;
            scanf("%d %d", &poly_index1, &poly_index2);

            if (poly_index1 < 1 || poly_index1 > num_polynomial || poly_index2 < 1 || poly_index2 > num_polynomial)
            {
                printf("Invalid polynomial selection.\n");
                continue;
            }

            multiply_polynomials(&polynomials[poly_index1 - 1], &polynomials[poly_index2 - 1]);
        }
        else if (choice == 9)
        {
            printf("Which two polynomial you want to divide(1-%d)", num_polynomial);
            int32_t poly_index1, poly_index2;
            scanf("%d %d", &poly_index1, &poly_index2);

            if (poly_index1 < 1 || poly_index1 > num_polynomial || poly_index2 < 1 || poly_index2 > num_polynomial)
            {
                printf("Invalid polynomial selection.\n");
                continue;
            }

            divide_polynomials(&polynomials[poly_index1 - 1], &polynomials[poly_index2 - 1]);
        }
    }

    for (int32_t i = 0; i < num_polynomial; i++)
    {
        free(polynomials[i].power);
        free(polynomials[i].coefficient);
        free(polynomials[i].name);
    }
    free(polynomials);

    return 0;
}

void printpolynomials(struct _polynomial *polynomials, int32_t num_polynomials)
{
    for (int32_t i = 0; i < num_polynomials; i++)
    {
        printf("%s:\n", polynomials[i].name);
        for (int32_t j = 0; j < polynomials[i].num_terms; j++)
        {
            if(polynomials[i].coefficient[j]<0)
            {
                printf("(%lf)x^%d", polynomials[i].coefficient[j], polynomials[i].power[j]);
            }
            else
            {
                printf("%lfx^%d", polynomials[i].coefficient[j], polynomials[i].power[j]);
            }
            if (j != (polynomials[i].num_terms - 1))
            {
                printf("+");
            }
        }
        printf("\n");
    }
}

void printcoefficient(int32_t x, struct _polynomial polynomial)
{
    for(int32_t i=0; i<polynomial.num_terms; i++)
    {
        if(polynomial.power[i] == x)
        {
            printf("coefficient is: %lf\n", polynomial.coefficient[i]);
            return;
        }
    }
    printf("coefficient is: 0\n");
    return;
}

void addelement(struct _polynomial *polynomial)
{
    int32_t new_power;

    printf("Enter the power for the new term: ");
    scanf("%d", &new_power);

    for (int32_t i = 0; i < polynomial->num_terms; i++)
    {
        if (polynomial->power[i] == new_power)
        {
            printf("Term with power %d already exists. Cannot add.\n", new_power);
            return;
        }
    }

    polynomial->num_terms++;

    polynomial->power = realloc(polynomial->power, (polynomial->num_terms) * sizeof(int32_t));
    polynomial->coefficient = realloc(polynomial->coefficient, (polynomial->num_terms) * sizeof(double));

    printf("Enter coefficient for term x^%d: ", new_power);
    scanf("%lf", &polynomial->coefficient[polynomial->num_terms - 1]);

    polynomial->power[polynomial->num_terms - 1] = new_power;

    printf("New term with power %d has been added.\n", new_power);

    for(int32_t i=0; i<polynomial->num_terms; i++)
    {
        for(int32_t j=i; j<polynomial->num_terms; j++)
        {
            if(polynomial->power[i] < polynomial->power[j])
            {
                int32_t temp = polynomial->power[i];
                polynomial->power[i] = polynomial->power[j];
                polynomial->power[j] = temp;
                temp = polynomial->coefficient[i];
                polynomial->coefficient[i] = polynomial->coefficient[j];
                polynomial->coefficient[j] = temp;
            }
        }
    }
}

void removeelement(struct _polynomial *polynomial)
{
    if (polynomial->num_terms == 0)
    {
        printf("Polynomial is empty. Cannot remove element.\n");
        return;
    }

    printf("Enter the power of the term you want to remove: ");
    int32_t power_to_remove;
    scanf("%d", &power_to_remove);

    int32_t index_to_remove = -1;

    for (int32_t i = 0; i < polynomial->num_terms; i++)
    {
        if (polynomial->power[i] == power_to_remove)
        {
            index_to_remove = i;
            break;
        }
    }

    if (index_to_remove == -1)
    {
        printf("Term with power %d not found in the polynomial.\n", power_to_remove);
        return;
    }

    for (int32_t i = index_to_remove; i < polynomial->num_terms - 1; i++)
    {
        polynomial->coefficient[i] = polynomial->coefficient[i + 1];
        polynomial->power[i] = polynomial->power[i + 1];
    }

    polynomial->num_terms--;

    polynomial->power = realloc(polynomial->power, polynomial->num_terms * sizeof(int32_t));
    polynomial->coefficient = realloc(polynomial->coefficient, polynomial->num_terms * sizeof(double));

    printf("Term with power %d has been removed from the polynomial.\n", power_to_remove);
}

void printcoefficients(struct _polynomial *polynomials, int32_t num_polynomials)
{
    printf("Which polynomial's coefficient you want to print:\n");
    for (int32_t i = 0; i < num_polynomials; i++)
    {
        printf("(%d)%s:\n", i, polynomials[i].name);
        for (int32_t j = 0; j < polynomials[i].num_terms; j++)
        {
            if(polynomials[i].coefficient[j]<0)
            {
                printf("(%lf)x^%d", polynomials[i].coefficient[j], polynomials[i].power[j]);
            }
            else
            {
                printf("%lfx^%d", polynomials[i].coefficient[j], polynomials[i].power[j]);
            }
            if (j != (polynomials[i].num_terms - 1))
            {
                printf("+");
            }
        }
        printf("\n");
    }
    printf("Your choice: ");
    int32_t choice;
    scanf("%d", &choice);
    printf("Which term: ");
    int32_t term;
    scanf("%d", &term);
    printcoefficient(term, polynomials[choice]);
}

void add_polynomials(struct _polynomial *p1, struct _polynomial *p2)
{
    struct _polynomial sum;
    int32_t max;
    int32_t element=0;

    if(p1->num_terms > p2->num_terms)
    {
        max = p1->num_terms;
    }
    else
    {
        max = p2->num_terms;
    }

    sum.power = malloc((p1->num_terms+p2->num_terms) * sizeof(int32_t));
    sum.coefficient = malloc((p1->num_terms+p2->num_terms) * sizeof(double));

    for(int32_t i=0; i<p1->num_terms; i++)
    {
        for(int32_t j=0; j<p2->num_terms; j++)
        {
            if(p1->power[i] == p2->power[j])
            {
                sum.coefficient[element] = p1->coefficient[i]+p2->coefficient[j];
                sum.power[element] = p1->power[i];
                element++;
                break;
            }
            else if(j==p2->num_terms-1)
            {
                sum.coefficient[element] = p1->coefficient[i];
                sum.power[element] = p1->power[i];
                element++;
            }
        }
    }

    for(int32_t i=0; i<p2->num_terms; i++)
    {
        for(int32_t j=0; j<p1->num_terms; j++)
        {
            if(p2->power[i] == p1->power[j])
            {
                break;
            }
            else if(j==p1->num_terms-1)
            {
                sum.coefficient[element] = p2->coefficient[i];
                sum.power[element] = p2->power[i];
                element++;
            }
        }
    }

    for(int32_t i=0; i<element; i++)
    {
        for(int32_t j=i; j<element; j++)
        {
            if(sum.power[i] < sum.power[j])
            {
                int32_t temp = sum.power[i];
                sum.power[i] = sum.power[j];
                sum.power[j] = temp;
                temp = sum.coefficient[i];
                sum.coefficient[i] = sum.coefficient[j];
                sum.coefficient[j] = temp;
            }
        }
    }

    for (int32_t i = 0; i < element; i++)
    {
        if(sum.coefficient[i]<0)
        {
            printf("(%lf)x^%d", sum.coefficient[i], sum.power[i]);
        }
        else
        {
            printf("%lfx^%d", sum.coefficient[i], sum.power[i]);
        }
        if (i != (element-1))
        {
            printf("+");
        }
        else
        {
            printf("\n");
        }
    }
    free(sum.power);
    free(sum.coefficient);
}

void subtract_polynomials(struct _polynomial *p1, struct _polynomial *p2)
{
    struct _polynomial sum;
    int32_t max;
    int32_t element=0;

    if(p1->num_terms > p2->num_terms)
    {
        max = p1->num_terms;
    }
    else
    {
        max = p2->num_terms;
    }

    sum.power = malloc((p1->num_terms+p2->num_terms) * sizeof(int32_t));
    sum.coefficient = malloc((p1->num_terms+p2->num_terms) * sizeof(double));

    for(int32_t i=0; i<p1->num_terms; i++)
    {
        for(int32_t j=0; j<p2->num_terms; j++)
        {
            if(p1->power[i] == p2->power[j])
            {
                sum.coefficient[element] = (p1->coefficient[i])-(p2->coefficient[j]);
                if(sum.coefficient[element]==0)
                {
                    break;
                }
                sum.power[element] = p1->power[i];
                element++;
                break;
            }
            else if(j==p2->num_terms-1)
            {
                sum.coefficient[element] = p1->coefficient[i];
                sum.power[element] = p1->power[i];
                element++;
            }
        }
    }

    for(int32_t i=0; i<p2->num_terms; i++)
    {
        for(int32_t j=0; j<p1->num_terms; j++)
        {
            if(p2->power[i] == p1->power[j])
            {
                break;
            }
            else if(j==p1->num_terms-1)
            {
                sum.coefficient[element] = (-1)*p2->coefficient[i];
                sum.power[element] = p2->power[i];
                element++;
            }
        }
    }

    if(element==0)
    {
        printf("0\n");
    }
    for(int32_t i=0; i<element; i++)
    {
        for(int32_t j=i; j<element; j++)
        {
            if(sum.power[i] < sum.power[j])
            {
                int32_t temp = sum.power[i];
                sum.power[i] = sum.power[j];
                sum.power[j] = temp;
                temp = sum.coefficient[i];
                sum.coefficient[i] = sum.coefficient[j];
                sum.coefficient[j] = temp;
            }
        }
    }
    for (int32_t i = 0; i < element; i++)
    {
        if(sum.coefficient[i]<0)
        {
            printf("(%lf)x^%d", sum.coefficient[i], sum.power[i]);
        }
        else
        {
            printf("%lfx^%d", sum.coefficient[i], sum.power[i]);
        }
        
        if (i != (element-1))
        {
            printf("+");
        }
        else
        {
            printf("\n");
        }
    }
    free(sum.power);
    free(sum.coefficient);
}

void multiply_polynomials(struct _polynomial *p1, struct _polynomial *p2)
{
    struct _polynomial sum;
    int32_t max;
    int32_t element=0;

    max = (p1->num_terms)*(p2->num_terms);

    sum.power = malloc(max * sizeof(int32_t));
    sum.coefficient = malloc(max * sizeof(double));

    for(int32_t i=0; i<p1->num_terms; i++)
    {
        for(int32_t j=0; j<p2->num_terms; j++)
        {
            sum.coefficient[element] = p1->coefficient[i]*p2->coefficient[j];
            sum.power[element] = p1->power[i]+p2->power[j];
            element++;
        }
    }

    for(int32_t i=0; i<max; i++)
    {
        for(int32_t j=0; j<max; j++)
        {
            if(sum.power[i]==sum.power[j] && i!=j)
            {
                sum.coefficient[i] += sum.coefficient[j];
                for (int32_t k = j; i < element; i++)
                {
                    sum.coefficient[k] = sum.coefficient[k + 1];
                    sum.power[k] = sum.power[k + 1];
                }
                element--;
                j--;
            }
        }
    }
    for(int32_t i=0; i<element; i++)
    {
        for(int32_t j=i; j<element; j++)
        {
            if(sum.power[i] < sum.power[j])
            {
                int32_t temp = sum.power[i];
                sum.power[i] = sum.power[j];
                sum.power[j] = temp;
                temp = sum.coefficient[i];
                sum.coefficient[i] = sum.coefficient[j];
                sum.coefficient[j] = temp;
            }
        }
    }

    for (int32_t i = 0; i < element; i++)
    {
        if(sum.coefficient[i]<0)
        {
            printf("(%lf)x^%d", sum.coefficient[i], sum.power[i]);
        }
        else
        {
            printf("%lfx^%d", sum.coefficient[i], sum.power[i]);
        }
        if (i != (element-1))
        {
            printf("+");
        }
        else
        {
            printf("\n");
        }
    }
    free(sum.power);
    free(sum.coefficient);
}

void divide_polynomials(struct _polynomial *p1, struct _polynomial *p2)
{
    int32_t max_degree_p1 = p1->power[0];
    int32_t max_degree_p2 = p2->power[0];

    if (max_degree_p1 < max_degree_p2)
    {
        printf("Q:\n0\n");
        printf("R:\n");
        for (int32_t i = 0; i < p1->num_terms; i++)
        {
            printf("%lf*x^%d", p1->coefficient[i], p1->power[i]);
            if (i != (p1->num_terms - 1))
            {
                printf(" + ");
            }
        }
        printf("\n");
    }
    else
    {
        int32_t max_degree_q = max_degree_p1 - max_degree_p2+1;

        double *quotient_coeff = (double *)calloc(max_degree_q, sizeof(double));
        double *remainder_coeff = (double *)calloc(max_degree_p1 + 1, sizeof(double));

        for (int32_t i = 0; i < p1->num_terms; i++)
        {
            remainder_coeff[p1->power[i]] = p1->coefficient[i];
        }

        while (max_degree_p1 >= max_degree_p2)
        {
            int32_t current_degree_q = max_degree_p1 - max_degree_p2;

            if (p2->coefficient[0] != 0)
            {
                double current_coeff_q = remainder_coeff[max_degree_p1] / p2->coefficient[0];

                quotient_coeff[current_degree_q] = current_coeff_q;

                for (int32_t i = 0; i < p2->num_terms; i++)
                {
                    int32_t current_power = max_degree_p1 - max_degree_p2 + p2->power[i];

                    remainder_coeff[current_power] -= current_coeff_q * p2->coefficient[i];
                }
            }

            while (max_degree_p1 >= 0 && remainder_coeff[max_degree_p1] == 0)
            {
                max_degree_p1--;
            }
        }

        printf("Q:\n");
        int32_t printed_terms = 0;
        for (int32_t i = max_degree_q; i >= 0; i--)
        {
            if (quotient_coeff[i] != 0)
            {
                if (printed_terms > 0)
                {
                    printf(" + ");
                }
                if(quotient_coeff[i]<0)
                {
                    printf("(%lf)x^%d", quotient_coeff[i], i );
                }
                else
                {
                    printf("%lfx^%d", quotient_coeff[i], i );
                }
                printed_terms++;
            }
        }
        if (printed_terms == 0)
        {
            printf("0");
        }
        printf("\n");
        int32_t Y=0;
        printf("R:\n");
        for (int32_t i = max_degree_p1; i >= 0; i--)
        {
            if(remainder_coeff[i]<0)
            {
                printf("(%lf)x^%d", remainder_coeff[i], i);
            }
            else
            {
                printf("%lfx^%d", remainder_coeff[i], i);
            }
            Y++;
            if (i != 0)
            {
                printf(" + ");
            }
        }
        if(Y==0)
        {
            printf("0");
        }
        printf("\n");

        free(quotient_coeff);
        free(remainder_coeff);
    }
}