#include <stdio.h>
#include <string.h>

char *sort(char *word) {
  int n = strlen(word);

  for (int i = 0; i <n-1; i++){
      for (int j = 0; j < n-i-1; j++) {
        if (word[j]>word[j+1]) {
          char temp = word[j];
          word[j] = word[j+1];
          word[j+1] = temp;
      }
    }
  }
  return word;

}


// char *sort(char *word) {
//   int j;
//   char key;
//   int n = strlen(word);
//   for (int i = 1; i<n;i++){
//     key = word[i];
//     j = i -1;
//
//     while (j >= 0 && word[j] > key) {
//       word[j+1] = word[j];
//       j = j -1 ;
//     }
//
//
//   word[j +1] = key;
// }
//   return word;
// }

int main() {
  int m, n;
  scanf("%d %d", &m, &n);

  char arr[m][50];
  char sort_arr[m][50];
  char dict[n][50];

  for(int i = 0; i<m;i++){
    scanf("%s", arr[i]);
    strcpy(sort_arr[i], arr[i]);
    sort(sort_arr[i]);

  }

  for(int j = 0; j<n; j++) {

   scanf("%s", dict[j]);

    char temp_dict[50];
    strcpy(temp_dict, dict[j]);
    sort(temp_dict);


   for(int k = 0; k<m; k++) {
      if (strcmp(temp_dict, sort_arr[k]) == 0 ) printf("%s ", arr[k]);

    }printf("\n");

  }
}
