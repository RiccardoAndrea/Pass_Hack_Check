#include "header.h"

/*spesso l persone usano come ultimo carattere della password uno speciale
inoltre spesso si usano le info personali recuperabili dai social  questo algoritmo usa tali informazioni chieste all'utente che sono nei social per creare password*/


char *capitalize_first_letter(char *str) {
  if (str == NULL || strlen(str) == 0) 
    return str;

  // Se la prima lettera è maiuscola, la trasformiamo in minuscola
  if (isupper(str[0])) {
      str[0] = tolower(str[0]);
  } else {
      // Se la prima lettera è minuscola, la trasformiamo in maiuscola
      str[0] = toupper(str[0]);
  }

  return str;  // Restituisce la stringa modificata
}

int check_case_combinations(char *str, int index, const char *password) {
  if (index == strlen(str)) {
      // Se siamo alla fine della stringa, confrontiamo la combinazione generata con la password target
      return strcmp(str, password) == 0;
  }

  // Salviamo il carattere originale
  char original = str[index];

  // Proviamo la lettera in minuscolo
  str[index] = tolower(original);
  if (check_case_combinations(str, index + 1, password)) {
      return 1;  // Se una combinazione ha funzionato, interrompiamo
  }

  // Proviamo la lettera in maiuscolo se è una lettera
  if (isalpha(original)) {
      str[index] = toupper(original);
      if (check_case_combinations(str, index + 1, password)) {
          return 1;
      }
  }

  // Ripristiniamo il carattere originale per non modificare la stringa chiamante
  str[index] = original;

  return 0;
}


int social_engigneering_force_attack(const char *info[], const char * password)
{
  const char *special[] = {
    "!", "\"", "#", "$", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/",
    ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "{", "|", "}", "~"
};


char crack_pass[1000];
int n = lunghezza_vettore_stringhe(info);
int dim_special = sizeof(special) / sizeof(special[0]); 
for(int i = 0; i < n; i++)
{
  printf("la crackpass:1 %s\n",info[i]);
  if(strcmp(info[i],password) == 0){
    return 1;
  }
  char temp[100];
  strcpy(temp,info[i]);
  if(check_case_combinations(temp,0,password)){
    return 1;
  }

  const char * temp2 = capitalize_first_letter(temp);

  if(brute_force_attack_with_base(temp2, password)){
    return 1;
  }
  if(brute_force_attack_with_base(info[i], password)){
    return 1;
  }

  for(int j = 0; j<n; j++)
  {
    strcpy(crack_pass, info[i]);
    strcat(crack_pass, info[j]);
    printf("la crackpass 2: %s\n",crack_pass);
    //risparmiamo tempo se e quella
    if(strcmp(crack_pass,password) == 0){
      return 1;
    }
    //cerchiamo tutti i possibili case sensitive
    if(check_case_combinations(crack_pass,0,password)){
      return 1;
    }
      for(int l = 0; l < n; l++)
      {
        strcpy(crack_pass, info[i]);
        strcat(crack_pass, info[j]);
        strcat(crack_pass, info[l]);
        printf("la crackpass 3: %s\n",crack_pass);
        if(strcmp(crack_pass,password) == 0)
        {
            return 1;
        }
        //cerchiamo tutti i possibili case sensitive
        if(check_case_combinations(crack_pass,0,password)){
          return 1;
        }
        for(int k = 0; k < dim_special; k++)
        {
            strcpy(crack_pass, info[i]);
            strcat(crack_pass, special[k]);
            printf("la crackpass 4: %s\n",crack_pass);
            // risparmiamo tempo
            if(strcmp(crack_pass,password) == 0){
              return 1;
            }
            //cerchiamo case sensitive
            if(check_case_combinations(crack_pass,0,password)){
              return 1;
            }
            strcpy(crack_pass, info[i]);
            strcat(crack_pass, info[j]);
            strcat(crack_pass, special[k]);
            printf("la crackpass 4: %s\n",crack_pass);
            if(strcmp(crack_pass,password) == 0){
                return 1;}
            //cerchiamo tutti i possibili case sensitive
            if(check_case_combinations(crack_pass,0,password)){
              return 1;
            }
            strcpy(crack_pass, info[i]);
            strcat(crack_pass, info[j]);
            strcat(crack_pass, info[l]);
            strcat(crack_pass, special[k]);
            printf("la crackpass 4: %s\n",crack_pass);
            if(strcmp(crack_pass,password) == 0){
                return 1;
            }
            //cerchiamo tutti i possibili case sensitive
            if(check_case_combinations(crack_pass,0,password)){
              return 1;
            }
        } 
      }
  }
  
}
return 0;

}




