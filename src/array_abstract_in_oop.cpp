#include <stdio.h>

class ClArray{
private:
    float data[100];
    int Size;
    int Length;

public:
    ClArray(){
        Size = 100;
        Length = 0;
    }

    void Append(float Vi){
        if(Length < Size){
            Length++;
            data[Length-1]=Vi;
        }
    }

    void Display(){
        for(int i=0; i<Length; i++){
            printf("%f, ",data[i]);
        }
        printf("\n");
    }

    void Insert(int index, float vi){
        if(ClArray::Length < ClArray::Size){
            for(int i=ClArray::Length; i>index; i--){
                ClArray::data[i] = ClArray::data[i-1];
            }
            ClArray::data[index] = vi;
            ClArray::Length++;
        }
    }

    void Delete(int index){
        if((ClArray::Length > 0) && (index >= 0)){
            for(int i=index; i<ClArray::Length; i++){
                ClArray::data[i] = ClArray::data[i+1];
            }
            ClArray::Length--;
        }
    }

    int Search(float vi){
        int result = -1;
        for (int i=0; i<ClArray::Length; i++){
            if(ClArray::data[i] == vi){
                result = i;
                break;
            }
        }
        return result;
    }

    float Get(int index){
        return ClArray::data[index];
    }

    void Set(int index, float vi){
        ClArray::data[index] = vi;
    }

    float Max(){
        float maxVal = ClArray::data[0];
        for(int i=1; i<ClArray::Length; i++){
            if(ClArray::data[i] > maxVal){
                maxVal = ClArray::data[i];
            }
        }
        return maxVal;
    }

    float Min(){
        float minVal = ClArray::data[0];
        for(int i=1; i<ClArray::Length; i++){
            if(ClArray::data[i] < minVal){
                minVal = ClArray::data[i];
            }
        }
        return minVal;
    }

    void Reverse(){
        float temp;
        for(int i=0, j=ClArray::Length-1; i<ClArray::Length/2; i++, j--){
            temp = ClArray::data[i];
            ClArray::data[i] = ClArray::data[j];
            ClArray::data[j] = temp;
        }
    }

    void Shift(char c, int n){  // c for 'l' or 'r', n for how many steps of the shift algorithm
        float temp;
        if((c == 'l') || (c == 'L')){
            for(int i=0; i<n; i++){  // looping for how many one-step shift will be performed
                temp = ClArray::data[0];  // save the first data index
                for(int j=0; j<ClArray::Length-1; j++){
                    ClArray::data[j] = ClArray::data[j+1];
                }
                ClArray::data[ClArray::Length-1] = temp;  // insert the temp
            }
        }
        else if((c == 'r') || (c == 'R')){
            for(int i=0; i<n; i++){  // looping for how many one-step shift will be performed
                temp = ClArray::data[ClArray::Length-1];  // save the last data index
                for(int j=ClArray::Length-1; j>0; j--){
                    ClArray::data[j] = ClArray::data[j-1];
                }
                ClArray::data[0] = temp;  // insert the temp
            }
        }
        else{
            printf("\nERROR !!! invalid parameter...\n");
        }
    }
};

int main(){
    class ClArray d;
    d.Append(1);
    d.Append(3);
    d.Append(5);
    d.Append(7);
    d.Display();
    printf("\n===============================\n");

    printf("\nInsert -1 di index ke 2\n");
    d.Insert(2, -1);
    d.Display();
    printf("\nDelete data di index ke 2\n");
    d.Delete(2);
    d.Display();
    printf("\n===============================\n");

    printf("\nSearch data yang bernilai 3\n");
    int n = d.Search(3);
    if(n == -1){
        printf("Data tidak ditemukan\n");
    } else{
        printf("Data bernilai 3 ada di index ke : %d\n", n);
        d.Display();

        printf("\nDelete data di index ke %d\n", n);
        d.Delete(d.Search(3));
        d.Display();
    }
    printf("\n===============================\n");

    int idx = 2;
    printf("\nAmbil nilai dari index ke %d ---> ", idx);
    printf("%f\n", d.Get(idx));
    printf("\nEdit data pada index ke %d menjadi bernilai 21\n", idx);
    d.Set(idx, 21);
    d.Display();
    printf("\n===============================\n");

    printf("\n");
    d.Display();
    printf("\nNilai maksimum : %f", d.Max());
    printf("\nNilai minimum : %f\n", d.Min());
    printf("\n===============================\n");

    printf("\nNambah beberapa data...\n");
    d.Append(9);
    d.Insert(2, 55);
    d.Insert(3, 11);
    d.Append(99);
    d.Display();
    printf("\nReverse array\n");
    d.Reverse();
    d.Display();
    printf("\n===============================\n");

    printf("\n");
    d.Display();
    printf("Shift 1 step to the left\n");
    d.Shift('l', 1);
    d.Display();
    printf("Shift 3 step to the right\n");
    d.Shift('r', 3);
    d.Display();
    printf("\n===============================\n");

    return 0;
}