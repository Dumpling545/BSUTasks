#pragma once
template <class DataT>
class SA_item {
    public:
        SA_item() : index( -1 ), info( DataT() ) {}
        SA_item( long i, DataT d ) : index( i ), info( d ) {}
        long index;
        DataT info;
};
