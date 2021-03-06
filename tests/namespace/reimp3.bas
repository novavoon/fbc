# include "fbcu.bi"

enum TEST_RES
	TEST_T1
	TEST_T2
	TEST_T3
end enum

namespace fbc_tests.ns.reimp3.foo 
 type t1 : __ as integer : end type
end namespace

namespace fbc_tests.ns.reimp3.bar 
    using foo
    function foobar overload (__ as t1) as TEST_RES
    	function = TEST_T1
	end function
end namespace

namespace fbc_tests.ns.reimp3.foo 
	type t2 : __ as integer : end type
	
	type t3 : __ as integer : end type
end namespace

namespace fbc_tests.ns.reimp3.bar 
    function foobar(__ as t2) as TEST_RES
    	function = TEST_T2
	end function

    function foobar(__ as t3) as TEST_RES
    	function = TEST_T3
	end function
end namespace


private sub test_proc cdecl
	using fbc_tests.ns.reimp3.bar
	
	CU_ASSERT( foobar( type<t1>( 0 ) ) = TEST_T1 )
	CU_ASSERT( foobar( type<t2>( 0 ) ) = TEST_T2 )
	CU_ASSERT( foobar( type<t3>( 0 ) ) = TEST_T3 )
end sub

private sub ctor () constructor

	fbcu.add_suite("fbc_tests.namespace.reimp3")
	fbcu.add_test("test", @test_proc)
	
end sub
