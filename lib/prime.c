
int isCPrime(int num) {
    for (int i=2; i < num; i++) 
        if(num % i == 0)  return 0;
        return (num !=1 && num !=0)? 1 : 0;
    
}

int checkCPrime(int scope) {
    int count = 0;
    for (int i=0;i<=scope;i++) {

        if(isCPrime(i) == 1) count++;

    }

    return count;
}
