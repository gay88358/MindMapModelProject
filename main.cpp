#include <gtest/gtest.h>
#include <iostream>

#include "./utCommandManager.h"
#include "./utComponent.h"

#include "./utNodeOperator.h"
#include "./utNodeModifier.h"
#include "./utNodeIdCounter.h"
#include "./utMindMapModel.h"
#include "./utMapFactory.h"
#include "./utComponentFactory.h"
#include "./utCommand.h"

using std::endl;
using std::cout;
using std::cin;

int main( int argc , char **argv )
{
    
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
}
