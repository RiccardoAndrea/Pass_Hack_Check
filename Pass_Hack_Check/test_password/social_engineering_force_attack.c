#include "header.h"

/*spesso l persone usano come ultimo carattere della password uno speciale
inoltre spesso le info personali come quelle recuperate sui social rendono
le password insicure. questo algoritmo usa tali informazioni chieste all'utente
per creare password usando la combinazione di tali info recuperate e nel caso
la pass non sia quella tenta anche di aggiunere caratteri speciali
alla fine della password */

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
  for(int j = 0; j<n; j++)
  {
    strcpy(crack_pass, info[i]);
    strcat(crack_pass, info[j]);
    printf("la crackpass 2: %s\n",crack_pass);
    if(strcmp(crack_pass,password) == 0){
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
        for(int k = 0; k < dim_special; k++)
        {
            strcpy(crack_pass, info[i]);
            strcat(crack_pass, special[k]);
            printf("la crackpass 4: %s\n",crack_pass);
            if(strcmp(crack_pass,password) == 0){
              return 1;
            }
            strcpy(crack_pass, info[i]);
            strcat(crack_pass, info[j]);
            strcat(crack_pass, special[k]);
            printf("la crackpass 4: %s\n",crack_pass);
            if(strcmp(crack_pass,password) == 0){
                return 1;}
            strcpy(crack_pass, info[i]);
            strcat(crack_pass, info[j]);
            strcat(crack_pass, info[l]);
            strcat(crack_pass, special[k]);
            printf("la crackpass 4: %s\n",crack_pass);
            if(strcmp(crack_pass,password) == 0){
                return 1;
            }
        } 
      }
  }
  
}
return 0;

}