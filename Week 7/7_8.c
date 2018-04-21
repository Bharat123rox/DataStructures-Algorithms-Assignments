#include <stdio.h>
#include <stdlib.h>
#define ll long long
#define f(i,a,b) for(ll i=a;i<b;i++)
#define fd(i,b,a) for(ll i=b;i>=a;i--)
#define null -1

#define parent(i)  ((i)-1)>>1
#define left(i)  (((i)<<1)+1)
#define right(i) (((i)<<1)+(1<<1))

struct heap
{
    int mi;
    int* A;
    int size;
};

typedef struct heap heap;

void create(heap *h, int type, int cap)
{
    h->mi = type;
    h->A = malloc(cap*sizeof(int));
    h->size = 0;
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void heapify(heap *h, int idx)
{
    int l,r, smallest, largest;
    l = left(idx);
    r = right(idx);
    if(h->mi)
    {
        if(l < h->size && h->A[l] < h->A[idx]) smallest = l;
        else smallest=idx;
        if(r < h->size && h->A[r] < h->A[smallest]) smallest = r;
        if(smallest!=idx) {
            swap(&(h->A[idx]), &(h->A[smallest]));
            heapify(h, smallest);
        }
    }
    else
    {
        if(l < h->size && h->A[l] > h->A[idx]) largest=l;
        else largest=idx;
        if(r < h->size && h->A[r] > h->A[largest]) largest=r;
        if(largest!=idx) {
            swap(&(h->A[idx]), &(h->A[largest]));
            heapify(h, largest);
        }
    }
}

void buildheap(heap *h)
{
    fd(i,h->size/2,0) {
        heapify(h, i);
    }
}

void push(heap *h, int key) 
{

    int idx = h->size;
    h->A[h->size] = key;
    h->size++;
    if(h->mi)
    {
        while((idx > 0) && (h->A[idx] < h->A[parent(idx)]) )
        {
            swap(&h->A[idx], &h->A[parent(idx)]);
            idx = parent(idx);
        }
    }
    else
    {
        while((idx > 0) && (h->A[idx] > h->A[parent(idx)]) )
        {
            swap(&(h->A[idx]), &(h->A[parent(idx)]));
            idx = parent(idx);
        }
    }
}

int top(heap *h)
{
    return h->A[0];
}

void pop(heap *h)
{
    h->A[0] = h->A[h->size-1];
    h->size--;
    heapify(h, 0);
}

void printh(heap *h)
{
    int i;
    f(i,0,h->size) printf("%d ",h->A[i]);
    printf("\n");
}

int main()
{
    int n,i,k,m1, m2;
    scanf("%d", &n);
    heap h;
    ll ans=0;
    create(&h, 1, n);
    f(i,0,n) {
        scanf("%d",&k);
        push(&h, k);
    }
    while(h.size > 1) {
        m1 = top(&h);
        pop(&h);
        m2 = top(&h);
        pop(&h);
        ans+=(m1+m2);
        push(&h, m1+m2);
    }
    printf("%lld\n",ans);
    return 0;
}
