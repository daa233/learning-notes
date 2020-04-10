#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
                HashSetHashFunction hashfn, HashSetCompareFunction comparefn,
                HashSetFreeFunction freefn)
{
  assert(elemSize > 0);
  assert(numBuckets > 0);
  assert(hashfn != NULL);
  assert(comparefn != NULL);
  h->elemSize = elemSize;
  h->numBuckets = numBuckets;
  h->size = 0;
  h->hashfn = hashfn;
  h->comparefn = comparefn;
  h->data = malloc(numBuckets * sizeof(vector));
  assert(h->data != NULL);
  for (int i = 0; i < h->numBuckets; ++i) {
    vector *v = h->data + i;
    VectorNew(v, elemSize, freefn, 0);  // use the default initial allocation
  }
}

void HashSetDispose(hashset *h)
{
  for (int i = 0; i < h->numBuckets; ++i) {
    vector *v = h->data + i;
    VectorDispose(v);
  }
  free(h->data);
}

int HashSetCount(const hashset *h)
{
  return h->size;
}

void HashSetEnter(hashset *h, const void *elemAddr)
{
  assert(elemAddr != NULL);
  int entry = h->hashfn(elemAddr, h->numBuckets);
  assert(entry >= 0 && entry <= h->numBuckets - 1);
  vector *v = h->data + entry;
  if (VectorLength(v) == 0) {
    VectorAppend(v, elemAddr);
  } else {
    int position = VectorSearch(v, elemAddr, h->comparefn, 0, true);
    if (position != -1) {
      VectorReplace(v, elemAddr, position);
    } else {
      VectorAppend(v, elemAddr);
    }
    VectorSort(v, h->comparefn);
  }
  h->size += 1;
}

void *HashSetLookup(const hashset *h, const void *elemAddr)
{ 
  assert(elemAddr != NULL);
  int entry = h->hashfn(elemAddr, h->numBuckets);
  assert (entry >= 0 && entry <= h->numBuckets - 1);
  vector *v = h->data + entry;
  if (VectorLength(v) > 0) {
    int position = VectorSearch(v, elemAddr, h->comparefn, 0, true);
    if (position != -1) {
      return (char *)v->data + position * h->elemSize;
    }
  }
  return NULL;
}

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData)
{
  assert(mapfn != NULL);
  for (int i = 0; i < h->numBuckets; ++i) {
    vector *v = h->data + i;
    VectorMap(v, mapfn, auxData);
  }
}