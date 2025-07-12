#include <zm/zm.h>

bool zVecListSVM(const zVecList *data1, const zVecList *data2, zVec *normal_estim, double *offset_estim)
{
  zMat q, a;
  zVec c, b, ans;
  zVecListCell *cp;
  int size, i, j;
  bool ret = false;

  if( zListIsEmpty( data1 ) || zListIsEmpty( data2 ) ){
    ZRUNERROR( "empty set specified" );
    return false;
  }
  size = zVecSizeNC(zListHead(data1)->data) + 1;
  if( !( *normal_estim = zVecAlloc( size - 1 ) ) )
    return false;

  q = zMatAllocSqr( size * 2 );
  c = zVecAlloc( size * 2 );
  a = zMatAlloc( zListSize(data1) + zListSize(data2), size * 2 );
  b = zVecAlloc( zListSize(data1) + zListSize(data2) );
  ans = zVecAlloc( size * 2 );
  if( !q || !c || !a || !b || !ans ) goto TERMINATE;

  zMatZero( q );
  for( i=0; i<size-1; i++ )
    for( j=0; j<size-1; j++ ){
      zMatSetElemNC( q,      i,      j, 1 );
      zMatSetElemNC( q,      i, size+j,-1 );
      zMatSetElemNC( q, size+i,      j,-1 );
      zMatSetElemNC( q, size+i, size+j, 1 );
    }
  zVecZero( c );
  i = 0;
  zListForEach( data1, cp ){
    for( j=0; j<zVecSizeNC(cp->data); j++ ){
      zMatSetElemNC( a, i,      j, zVecElemNC(cp->data,j) );
      zMatSetElemNC( a, i, size+j,-zVecElemNC(cp->data,j) );
    }
    zMatSetElemNC( a, i,   size, 1 );
    zMatSetElemNC( a, i, 2*size,-1 );
    zVecSetElemNC( b, i, 1 );
    i++;
  }
  zListForEach( data2, cp ){
    for( j=0; j<zVecSizeNC(cp->data); j++ ){
      zMatSetElemNC( a, i,      j,-zVecElemNC(cp->data,j) );
      zMatSetElemNC( a, i, size+j, zVecElemNC(cp->data,j) );
    }
    zMatSetElemNC( a, i,   size,-1 );
    zMatSetElemNC( a, i, 2*size, 1 );
    zVecSetElemNC( b, i, 1 );
    i++;
  }
  if( zQPSolveLemke( q, c, a, b, ans, NULL ) ){
    for( i=0; i<size-1; i++ )
      zVecSetElemNC( *normal_estim, i, zVecElemNC(ans,i)-zVecElemNC(ans,size+i) );
    *offset_estim = zVecElemNC(ans,size-1)-zVecElemNC(ans,2*size-1);
    ret = true;
  }

 TERMINATE:
  zMatFreeAtOnce( 2, q, a );
  zVecFreeAtOnce( 3, c, b, ans );
  return ret;
}




void generate_hyperplane(zVec normal, double *offset)
{
  zVecRandUniform( normal, -1, 1 );
  zVecNormalizeDRC( normal );
  *offset = zRandF( -1, 1 );
}

int check_region(zVec sample, const zVec normal, const double offset)
{
  return zVecInnerProd( sample, normal ) + offset > 0 ? 1 : -1;
}

void generate_sample(zVecList *data1, zVecList *data2, const zVec normal, const double offset, const int num)
{
  zVec sample;
  int k;

  for( k=0; k<num; k++ ){
    sample = zVecAlloc( zVecSizeNC(normal) );
    zVecRandUniform( sample, -10, 10 );
    if( check_region( sample, normal, offset ) == 1 )
      zVecListInsertHead( data1, sample );
    else
      zVecListInsertHead( data2, sample );
  }
}

void output_sample(const zVecList *data, const char *filename)
{
  FILE *fp;
  zVecListCell *cp;

  fp = fopen( filename, "w" );
  zListForEach( data, cp ){
    zVecValueFPrint( fp, cp->data );
  }
  fclose( fp );
}


int main(int argc, char *argv[])
{
  zVecList data1, data2;
  zVec normal, normal_estim;
  double offset, offset_estim;
  const int num = 1000;

  zRandInit();
  zListInit( &data1 );
  zListInit( &data2 );
  normal = zVecAlloc( 2 );
  generate_hyperplane( normal, &offset );
  generate_sample( &data1, &data2, normal, offset, num );
  output_sample( &data1, "1" );
  output_sample( &data2, "2" );

  zVecListSVM( &data1, &data2, &normal_estim, &offset_estim );

zVecPrint( normal );
printf( "%g\n", offset );
zVecPrint( normal_estim );
printf( "%g\n", offset_estim );

  zVecFree( normal );
  zVecFree( normal_estim );
  zVecListDestroy( &data1 );
  zVecListDestroy( &data2 );
  return 0;
}
