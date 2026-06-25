#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <limits>

struct mon{
    int serial;
    int price;
    char brand[16];
    char model[21];
    bool hasTuner;
    mon* next;
    mon* prev;
};
struct s_mon{
    int serial;
    int price;
    char model[21];
    char brand[16];
    bool hasTuner;
};
void push(mon*& front,mon*& back,const char* brand,const char* model,
          int sr,int price,bool hasTuner){
    mon* tmp= new mon;
    tmp->serial = sr;
    std::strncpy(tmp->brand, brand, sizeof(tmp->brand) - 1);
    tmp->brand[sizeof(tmp->brand) - 1] = '\0';
    std::strncpy(tmp->model, model, sizeof(tmp->model) - 1);
    tmp->model[sizeof(tmp->model) - 1] = '\0';  
    tmp->price= price;
    tmp->hasTuner= hasTuner;
    tmp->prev=nullptr;
    tmp->next=front;
    if(front==nullptr){
        front = back = tmp;
    }
    else{
        front->prev=tmp;
        front=tmp;
    }
}
void pop(mon*& front,mon*& back){
    if(front==nullptr){
        std::cout<<"Already empty"<<std::endl;
        return;
    }
    else if(front->next==nullptr){
        delete front;
        front = back = nullptr;
    }
    else{
        mon* tmp=front;
        front=front->next;
        front->prev=nullptr;
        delete tmp;
    }
}
void popAtIndex(mon*& front,mon*& back,int index){
    if(front==nullptr){
        std::cout<<"Already empty"<<std::endl;
        return;
    }
    else if(front->next==nullptr){
        if(index==0){
        delete front;
        front=back=nullptr;
        }
        else{
            std::cout<<"No such element!"<<std::endl;
            return; 
        }
    }
    else{
        mon* tmp=front;
        for(int i=0;i<index && tmp;i++){
            tmp=tmp->next;
        }
        if(tmp==front){
            front=front->next;
            front->prev=nullptr;
            delete tmp;
            return;
        }
        if(tmp==nullptr){
            std::cout<<"No node at that index"<<std::endl;
            return;
        }
        if(tmp->next){
        tmp->prev->next= tmp->next;
        tmp->next->prev=tmp->prev;
        }
        else{
            back=tmp->prev;
            back->next=nullptr;
        }
        delete tmp;
    }
}
void PrintMon(mon* front) {
    if (front == nullptr) {
        std::cout << "There are no monitors present." << std::endl;
        return;
    }

    std::cout << std::left
              << std::setw(10) << "Serial"
              << std::setw(12) << "Brand"
              << std::setw(20) << "Model"
              << std::setw(12) << "Has Tuner"
              << std::setw(8) << "Price" << std::endl;

    while (front) {
        std::cout << std::left
                  << std::setw(10) << front->serial
                  << std::setw(12) << front->brand
                  << std::setw(20) << front->model
                  << std::setw(12) << (front->hasTuner ? "Yes" : "No")
                  << std::setw(8) << front->price << std::endl;
        front = front->next;
    }
}
void PrintCurr(mon* front){
    std::cout << std::left
                  << std::setw(10) << front->serial
                  << std::setw(12) << front->brand
                  << std::setw(20) << front->model
                  << std::setw(12) << (front->hasTuner ? "Yes" : "No")
                  << std::setw(8) << front->price << std::endl;
}
void RegularSearch(mon*front,const char* target,const char* by){
    if(!strcmp(by,"Brand") || !strcmp(by,"brand")){
        while(front && strcmp(front->brand,target)!=0){
            front=front->next;
        }
        if(front==nullptr){
            std::cout<<"No matching Brand"<<std::endl;
            return;
        }
        PrintCurr(front);
    }
    if(!strcmp(by,"Model") || !strcmp(by,"model")){
        while(front && strcmp(front->model,target)!=0){
            front=front->next;
        }
        if(front==nullptr){
            std::cout<<"No matching Model"<<std::endl;
            return;
        }
        PrintCurr(front);
    }
}
void RegularSearchInt(mon* front,const char* by,int target){
    if(!strcmp(by,"Serial") || !strcmp(by,"serial")){
        while(front && front->serial!=target){
            front=front->next;
        }
        if(front==nullptr){
            std::cout<<"No matching serial number with the target."<<std::endl;
            return;
        }
        PrintCurr(front);
    }
    if(!strcmp(by,"Price") || !strcmp(by,"price")){
        while(front && front->price!=target){
            front=front->next;
        }
        if(front==nullptr){
            std::cout<<"No matching price number with the target."<<std::endl;
            return;
        }
        PrintCurr(front);
    }
}
void pushBack(mon*& front,mon*& back,const char* brand,const char* model,
          int sr,int price,bool hasTuner){
            mon* tmp= new mon;
            tmp->serial = sr;
            std::strncpy(tmp->brand, brand, sizeof(tmp->brand) - 1);
            tmp->brand[sizeof(tmp->brand) - 1] = '\0';
            std::strncpy(tmp->model, model, sizeof(tmp->model) - 1);
            tmp->model[sizeof(tmp->model) - 1] = '\0';  
            tmp->price= price;
            tmp->hasTuner= hasTuner;
            tmp->prev=back;
            tmp->next=nullptr;
            if(front==nullptr){
                tmp->prev=nullptr;
                front = back = tmp;
            }
            else{
                back->next= tmp;
                back = tmp;
            }
          }
void swapMon(mon* a, mon* b) {
    std::swap(a->serial, b->serial);
    std::swap(a->price, b->price);
    std::swap(a->hasTuner, b->hasTuner);
    char tmpBrand[16], tmpModel[21];
    std::strcpy(tmpBrand, a->brand);
    std::strcpy(tmpModel, a->model);
    std::strcpy(a->brand, b->brand);
    std::strcpy(a->model, b->model);
    std::strcpy(b->brand, tmpBrand);
    std::strcpy(b->model, tmpModel);
}
void toLowerCase(char* str){
    for(int i=0;str[i];++i){
        if(str[i]>='A' && str[i]<='Z')str[i]+=32;
    }
}
mon* partitionInt(mon* low,mon* high,const char* order,const char* by){
    int pivot;
    if(!strcmp(by,"price") || !strcmp(by,"Price") || !strcmp(by,"PRICE")){
        pivot= high->price;
    }
    else pivot= high->serial;
    mon* i= low->prev;
    bool compare = false;
    for(mon* j=low; j!=high;j=j->next){
        if(!strcmp(by,"price") || !strcmp(by,"Price") || !strcmp(by,"PRICE")){
        compare= (!strcmp(order,"asc")) ? (j->price<pivot) : (j->price>pivot);
        }
        else compare= (!strcmp(order,"asc")) ? (j->serial<pivot) : (j->serial>pivot);

        if(compare){
            i= (i==nullptr) ? low: i->next;
            swapMon(i,j);
        }
    }
    i =(i==nullptr)? low:i->next;
    swapMon(i,high);
    return i;
}
void quickSort(mon* low, mon* high, const char* order,const char* by) {
    if (high != nullptr && low != high && low != high->next) {
        mon* p = partitionInt(low, high, order,by);
        quickSort(low, p->prev, order,by);
        quickSort(p->next, high, order,by);
    }
}

void SortMon(mon*& front, mon*& back, const char* by, const char* order = "asc") {
    if (front == nullptr) {
        std::cout << "There are no monitors to sort" << std::endl;
        return;
    }

    if (!strcmp(by, "price") || !strcmp(by, "Price") || !strcmp(by, "PRICE") ||
        !strcmp(by, "serial") || !strcmp(by, "Serial") || !strcmp(by, "SERIAL")) {
        quickSort(front, back, order, by);
        std::cout << "Sorted by " << by << " (" << order << ").\n";
    } else {
        std::cout << "Sorting by '" << by << "' is not supported.\n";
    }
}
int sizeOfList(mon*front){
    int cnt=0;
    while(front){
        cnt++;
        front = front->next;
    }
    return cnt;
}
void pushAtIndex(mon*& front,mon*& back,const char* brand,const char* model,
    int sr,int price,bool hasTuner,int index,int size){
        mon* newMon = new mon;
        newMon->hasTuner= hasTuner;
        newMon->price = price;
        newMon->serial= sr;
        std::strncpy(newMon->brand, brand, sizeof(newMon->brand) - 1);
        newMon->brand[sizeof(newMon->brand) - 1] = '\0';
        std::strncpy(newMon->model, model, sizeof(newMon->model) - 1);
        newMon->model[sizeof(newMon->model) - 1] = '\0';
        newMon->next=nullptr;
        newMon->prev=nullptr;
        if(front==nullptr){
            front = back = newMon;
            return;
        }
        else{
            if(index >= size){
                mon* temp = back;
                back->next = newMon;
                back= back->next;
                back->prev = temp;
                return;
            }
            else if(index == 0){
                mon* temp= front;
                front= newMon;
                front->next=temp;
                front->prev=nullptr;
                temp->prev=front; 
                return;   
            }
            else{
                mon* temp = front;
                for(int i=0;i<index && temp;i++){
                    temp=temp->next;
                }
                if(temp==nullptr){
                    std::cout<<"Something went wrong"<<std::endl;
                    return;
                }
                newMon->prev=temp->prev;
                newMon->next=temp;
                temp->prev->next=newMon;
                temp->prev=newMon;
            }
        }   
    }
    void LinkedListToArr(mon* front,s_mon arr[],int sizeOfLlist,int arrsize){
        if(arrsize < sizeOfLlist){
            std::cout<<"List too big for the arrray"<<std::endl;
            return;
        }
        for(int i=0;front && i<sizeOfLlist;i++){
            strncpy(arr[i].brand,front->brand,sizeof(arr[i].brand)-1);
            arr[i].brand[sizeof(arr[i].brand)-1]='\0';
            strncpy(arr[i].model,front->model,sizeof(arr[i].model)-1);
            arr[i].model[sizeof(arr[i].model)-1]='\0';
            arr[i].serial=front->serial;
            arr[i].price=front->price;
            arr[i].hasTuner= front->hasTuner;
            front=front->next;
        }
    }
    mon* getMiddle(mon* low,mon* high){
        if(low==nullptr)return nullptr;
        mon* slow=low;
        mon* fast=low;
        while(fast!=high && fast->next!=high){
            fast=fast->next;
            if(fast!=high){
                fast=fast->next;
                slow=slow->next;
            }
        }
        return slow;
            
    }
    mon* BinarySearch(mon* front,int targetSerial){
        mon* low = front;
        mon* high = nullptr;
        while(low !=high){
            mon* mid = getMiddle(low,high);
            if(mid==nullptr)return nullptr;
            if(mid->serial==targetSerial)return mid;
            else if(targetSerial<mid->serial){
                high=mid;
            }
            else{
                low=mid->next;
            }
        }
        return nullptr;
    }
    s_mon* s_BinarySearch(s_mon arr[],int size,int targetSerial){
        int low= 0;
        int high = size-1;
        while(low <= high){
            int mid =(low + high)/2;
            if(arr[mid].serial==targetSerial)return &arr[mid];
            else if(targetSerial < arr[mid].serial)high = mid-1;
            else low = mid+1;
        }
        return nullptr;
    }
    s_mon* sp_BinarySearch(s_mon arr[],int size,int targetPrice){
        int low =0;
        int high= size-1;
        while(low<=high){
            int middle= (high+low)/2;
            if(arr[middle].price==targetPrice)return &arr[middle];
            else if(arr[middle].price > targetPrice)high = middle-1;
            else low = middle+1;
        }
        return nullptr;
    }
    void ClearList(mon*& front){
        while(front){
            mon* temp=front;
            front=front->next;
            delete temp;
        }
    }
    void ConvertArrLLtoArr(mon* front,s_mon arr[],int ammount,int size){
        if(ammount > size || front == nullptr){
            std::cout<<"The amount is too high for this array"<<std::endl;
            return;
        }
        for(int i=0;i<ammount && front;++i){

            strncpy(arr[i].brand,front->brand,sizeof(arr[i].brand)-1);
            arr[i].brand[sizeof(arr[i].brand)-1]='\0';
            strncpy(arr[i].model,front->model,sizeof(arr[i].model)-1);
            arr[i].model[sizeof(arr[i].model)-1]='\0';
            arr[i].serial=front->serial;
            arr[i].price=front->price;
            arr[i].hasTuner= front->hasTuner;
                
            front=front->next;
        }
    }
    void s_monSwap(s_mon& f,s_mon& s){
        s_mon tmp=f;
        f = s;
        s = tmp;
    }
    void s_ExchangeSort(s_mon arr[],int size){
        for(int i=0;i<size;++i){
            for(int j=i+1;j<size;++j){
                if(arr[i].price > arr[j].price)s_monSwap(arr[i],arr[j]);
            }
        }
    }
    int s_Partition(s_mon arr[],int low, int high){
        int pivot = arr[high].price;
        int i=low-1;
        int j=low;
        for(;j<high;++j){
            if(arr[j].price<pivot){
                s_monSwap(arr[j],arr[i]);
                i++;
            }
        }
        s_monSwap(arr[i+1],arr[high]);
        return i+1;
    }
    void s_qsort(s_mon arr[],int low,int high){
        if(low<high){
            int partition_index= s_Partition(arr,low,high);
            s_qsort(arr, low, partition_index-1);
            s_qsort(arr, partition_index+1, high);
        }
    }
    void BubbleSortMon(mon* front,int size){
        int i=0;
        bool swapped;
        for(;i<size-1;++i){
            swapped=false;
            mon* j= front;
            for(;j && j->next;j=j->next){
                if(j->price<j->next->price){
                swapMon(j,j->next);
                swapped=true;
                }
            }
            if(swapped==false)break;
        }
    }
    void bsortBrandAndPrice(mon* front,int size){
        int i=0;
        bool swapped;
        for(;i<size-1;++i){
            swapped=false;
            mon* j= front;
            for(;j && j->next;j=j->next){
                if(strcmp(j->brand,j->next->brand)>=0 || j->price<j->next->price){
                swapMon(j,j->next);
                swapped=true;
                }
            }
            if(swapped==false)break;
        }
    }
    void PrintSelectedBrand(mon* front,const char* selectBrand){
        if(front==nullptr){
            std::cout<<"The list is empty"<<std::endl;
            return;
        }
        int cnt=0;
        while(front){
            if(!strcmp(front->brand,selectBrand)){
            PrintCurr(front);
            cnt++;
            }
            front=front->next;
        }
        
        std::cout<<"There we found "<<cnt<<" monitors with brand: "<<selectBrand
        <<"\n--Print Completed--"<<std::endl;
    }
    void InsertionSort(s_mon arr[],int size){
        for(int i=1;i<size;++i){
            s_mon key = arr[i];
            int j= i-1;
            while(j >=0 && arr[j].price > key.price){
                arr[j+1] = arr[j];
                --j;
            }
            arr[j+1]=key;
        }
    }
    void merge(s_mon arr[], int left, int mid, int right){
        int n1 = mid-left +1;
        int n2 = right-mid;
        s_mon* L= new s_mon[n1];
        s_mon* R= new s_mon[n2];
        for(int i=0;i<n1;++i){
            L[i] = arr[left+ i];
        }
        for(int j=0;j<n2;++j){
            R[j]= arr[mid+j+1];
        }
        int i=0,j=0,k=left;
        while(i<n1 && j<n2){
            if(L[i].price <= R[j].price){
                arr[k]=L[i];
                ++i;
            }
            else{
                arr[k]=R[j];
                ++j;
            }
            ++k;
        }
        while(i<n1){
            arr[k++]=L[i++];
        }
        while(j<n2){
            arr[k++]=R[j++];
        }
        delete[] L;
        delete[] R;
    }
    void mergeSort(s_mon arr[], int left,int right){
        if(left<right){
            int mid = (left+right) /2;
            mergeSort(arr,left,mid);
            mergeSort(arr,mid+1,right);
            merge(arr,left,mid,right);
        }
    }
    void LoadFromFile(mon*& back,mon*& front,const char* fname){
        std::ifstream f(fname);
        if(!f.is_open()){
            std::cout<<"Failed to open the file"<<std::endl;
            return;
        }
        int serial;
        char brand[16];
        char model[21];
        bool hasTuner;
        int price;
        int cnt=0;
        while(f >> serial >> brand >> model >> hasTuner >> price){
            pushBack(front,back,brand,model,serial,price,hasTuner);
            cnt++;
        }
        f.close();
        std::cout<<"Data loaded from file"<<"Total monitors: "<<cnt<<std::endl;
    }
    bool safeIntInput(int& value,const char* prompt){
        while(true){
            std::cout<<prompt<<" ";
            std::cin>>value;
            if(std::cin.eof()){
                std::cout<<"EOF trigered"<<std::endl;
                return false;
            }
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout<<"Invalid input. Please enter an integer."<<std::endl;
            }
            else{
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                return true;
            }
        }
    }
    bool safeBoolInput(bool& dest,const char* prompt){
        int tmp;
        while (true){
            std::cout<<prompt;
            std::cin>>tmp;
            if(std::cin.eof()){
                std::cout<<"\nBad Input. Likely cause: ctr+z on windows or cmd+d on mac or ctr+d on linux dont press those during input of a type other than string/cstring!"<<std::endl;
                return false;
            }
            if(std::cin.fail() || (tmp!=0 && tmp!=1)){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout<<"Invalid input. Please enter a 1(true) or 0(false)."<<std::endl;
            }
            else{
                dest = static_cast<bool>(tmp);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                return true;
            }
        }
    }
    bool safeCstringInput(char* dest,const char* prompt,int max_size){
        while (true){
            std::cout<<prompt;
            std::cin.getline(dest,max_size);
            if(std::cin.eof()){
                std::cout<<"\nEOF detected. Exiting input."<<std::endl;
                return false;
            }
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout<<"Invalid input. Please enter a valid string /string size."<<std::endl;
            }
            else if(strnlen(dest,max_size)==0){
                std::cout<<"CANT BE EMPTY, try again."<<std::endl;
            }
            else{
                return true;
            }
        }
    }
    void properArrPrint(s_mon arr[],int size){
        std::cout << std::left
              << std::setw(10) << "Serial"
              << std::setw(12) << "Brand"
              << std::setw(20) << "Model"
              << std::setw(12) << "Has Tuner"
              << std::setw(8) << "Price" << std::endl;
        for(int i=0;i<size;++i){
        std::cout << std::left
                  << std::setw(10) << arr[i].serial
                  << std::setw(12) << arr[i].brand
                  << std::setw(20) << arr[i].model
                  << std::setw(12) << (arr[i].hasTuner ? "Yes" : "No")
                  << std::setw(8) << arr[i].price << std::endl;
    }
    }
    void singleArrPrint(s_mon arr[]){
        std::cout << std::left
              << std::setw(10) << "Serial"
              << std::setw(12) << "Brand"
              << std::setw(20) << "Model"
              << std::setw(12) << "Has Tuner"
              << std::setw(8) << "Price" << std::endl;
        std::cout << std::left
                  << std::setw(10) << arr->serial
                  << std::setw(12) << arr->brand
                  << std::setw(20) << arr->model
                  << std::setw(12) << (arr->hasTuner ? "Yes" : "No")
                  << std::setw(8) << arr->price << std::endl;
    }
    
        //=================== M A I N ======================
        int main() {
            mon* front = nullptr;
            mon* back = nullptr;
            constexpr int maxArraySize = 100;
            s_mon arr[maxArraySize];
        
            int listSize = 0;
            int arraySize = 0;
        
            
            char loadChoice;
            std::cout << "Load monitors from file? (Y/N): ";
            std::cin >> loadChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
            if (loadChoice == 'Y' || loadChoice == 'y') {
                char filename[100];
                if(!safeCstringInput(filename, "Enter filename to load: ", 100))return 0;
                LoadFromFile(back, front, filename);
            }
        
            int choice;
        
            do {
                std::cout << "\n==== Monitor Management Menu ====\n";
                std::cout << "1. Add new monitor\n";
                std::cout << "2. Print all monitors\n";
                std::cout << "3. Search monitor (Linked List)\n";
                std::cout << "4. Search monitor (Array)\n";
                std::cout << "5. Sort first 10 monitors (Array - ExchangeSort)\n";
                std::cout << "6. Sort entire linked list (Bubble Sort)\n";
                std::cout << "7. Sort array (Insertion Sort or Merge Sort)\n";
                std::cout << "8. Print monitors by selected brand\n";
                std::cout << "9. Clear monitor list\n";
                std::cout << "0. Exit\n";
                if(!safeIntInput(choice, "Enter your choice: "))return 0;
        
                switch (choice) {
                    case 1: {
                        int serial, price;
                        char brand[16], model[21];
                        bool hasTuner;
        
                        safeIntInput(serial, "Enter serial number: ");
                        safeCstringInput(brand, "Enter brand: ", 16);
                        safeCstringInput(model, "Enter model: ", 21);
                        safeBoolInput(hasTuner, "Has tuner?");
                        safeIntInput(price, "Enter price: ");
        
                        push(front, back, brand, model, serial, price, hasTuner);
                        std::cout << "Monitor added successfully!\n";
                        break;
                    }
        
                    case 2:
                        PrintMon(front);
                        break;
        
                    case 3: {
                        int targetSerial;
                        if(!safeIntInput(targetSerial, "Enter serial number to search (Linked List): "))return 0;
                        mon* result = BinarySearch(front, targetSerial);
                        if (result) {
                            std::cout << "Monitor found in linked list:\n";
                            PrintCurr(result);
                        } else {
                            std::cout << "Monitor not found in linked list.\n";
                        }
                        break;
                    }
        
                    case 4: {
                        int size = sizeOfList(front);
                        if (size == 0) {
                            std::cout << "No monitors loaded.\n";
                            break;
                        }
                        LinkedListToArr(front, arr, size, maxArraySize);
        
                        int targetSerial;
                        if(!safeIntInput(targetSerial, "Enter serial number to search (Array): "))return 0;
                        s_mon* result = s_BinarySearch(arr, size, targetSerial);
                        if (result) {
                            singleArrPrint(result);
                        } else {
                            std::cout << "Monitor not found in array.\n";
                        }
                        break;
                    }
        
                    case 5: {
                        int size = sizeOfList(front);
                        if (size < 10) {
                            std::cout << "Not enough monitors to sort 10 (only " << size << " monitors).\n";
                            break;
                        }
                        LinkedListToArr(front, arr, 10, maxArraySize);
                        s_ExchangeSort(arr, 10);
                        std::cout << "First 10 monitors sorted by Exchange Sort (Array):\n";
                        properArrPrint(arr,10);
                        break;
                    }
        
                    case 6: {
                        int size = sizeOfList(front);
                        if (size == 0) {
                            std::cout << "No monitors to sort.\n";
                            break;
                        }
                        BubbleSortMon(front, size);
                        std::cout << "Linked list sorted (Bubble Sort by price descending).\n";
                        break;
                    }
        
                    case 7: {
                        int size = sizeOfList(front);
                        if (size < 10) {
                            std::cout << "Not enough monitors to sort.\n";
                            break;
                        }
                        LinkedListToArr(front, arr, 10, maxArraySize);
        
                        int sortChoice;
                        std::cout << "Choose array sort method:\n";
                        std::cout << "1. Insertion Sort\n";
                        std::cout << "2. Merge Sort\n";
                        if(!safeIntInput(sortChoice, "Enter your choice: "))return 0;
        
                        if (sortChoice == 1) {
                            InsertionSort(arr, 10);
                            std::cout << "Sorted first 10 monitors by Insertion Sort.\n";
                        } else if (sortChoice == 2) {
                            mergeSort(arr, 0, 9);
                            std::cout << "Sorted first 10 monitors by Merge Sort.\n";
                        } else {
                            std::cout << "Invalid sorting choice.\n";
                        }
        
                        properArrPrint(arr,10);
                        break;
                    }
        
                    case 8: {
                        char brandSearch[16];
                        if(!safeCstringInput(brandSearch, "Enter brand to print monitors: ", 16))return 0;
                        PrintSelectedBrand(front, brandSearch);
                        break;
                    }
        
                    case 9:
                        ClearList(front);
                        back = nullptr;
                        std::cout << "Monitor list cleared.\n";
                        break;
        
                    case 0:
                        std::cout << "Exiting program. Goodbye!\n";
                        ClearList(front);
                        back = nullptr;
                        break;
        
                    default:
                        std::cout << "Invalid menu choice. Try again.\n";
                        break;
                }
        
            } while (choice != 0);
        
            return 0;
        }
        
