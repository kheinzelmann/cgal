
/*!
\ingroup PkgCombinatorialMapsConcepts
\cgalConcept

The concept `BasicDart` defines a <I>d</I>-dimensional dart for basic maps. A dart mainly stores handles to the darts linked with itself by \tred{the different applications of the basic map}. Moreover, it stores also handles to each non void attribute associated with itself.

\cgalHeading{Creation}

A dart `d0` is never constructed directly, but always created within a basic map `bm` by using the method \link BasicMap::create_dart `bm.create_dart()`\endlink. A new dart is initialized to be <I>i</I>-free, \f$ \forall\f$<I>i</I>: 0\f$ \leq\f$<I>i</I>\f$ \leq\f$<I>dimension</I>, and having all its attribute handles initialized to `NULL`, for each non `void` attribute.

\cgalHasModel \link CGAL::Dart `CGAL::Dart<d,CMap>`\endlink
\cgalHasModel \link CGAL::GMap_dart `CGAL::GMap_dart<d,GMap>`\endlink

*/

class BasicDart {
public:

/// \name Constants
/// @{

/*!
The dimension of the dart.
*/
static unsigned int dimension;

/// @}

/// \name Types
/// @{

/*!
%Dart handle type. Must be a model of `Handle` concept.
*/
typedef unspecified_type Dart_handle;

/*!
%Dart const handle type. Must be a model of `ConstHandle` concept.
*/
typedef unspecified_type Dart_const_handle;

/*!
`Attribute_handle<i>::%type` is a handle to `i`-attributes, with 0 \f$ \leq \f$ `i` \f$ \leq \f$ `dimension`. Must be a model of `Handle` concept.
\note It can be implemented using a nested template class.
*/
template <unsigned int i>
using Attribute_handle = unspecified_type;

/*!
`Attribute_const_handle<i>::%type` is a const handle to `i`-attributes, with 0 \f$ \leq \f$ `i` \f$ \leq \f$ `dimension`. Must be a model of `ConstHandle` concept.
\note It can be implemented using a nested template class.
*/
template <unsigned int i>
using Attribute_const_handle = unspecified_type;

/// @}

/// \name Access Member Functions
/// @{

/*!
To simplify a future implementation, it is recommended to not use this function and to use \link BasicMap::attribute `cm.attribute(dh)`\endlink instead.
Returns a handle to the <I>i</I>-attribute associated to the dart.
\pre 0\f$ \leq\f$<I>i</I>\f$ \leq\f$<I>dimension</I>, and <I>i</I>-attributes are non `void`.
*/
template <unsigned int i> Attribute_handle<i>::type attribute();

/*!
To simplify a future implementation, it is recommended to not use this function and to use \link BasicMap::attribute `cm.attribute(dh)`\endlink instead.
Returns a const handle to the <I>i</I>-attribute associated to the dart, when the dart is const. 
\pre 0\f$ \leq\f$<I>i</I>\f$ \leq\f$<I>dimension</I>, and <I>i</I>-attributes are non `void`.
*/
template <unsigned int i>
Attribute_const_handle<i>::type attribute() const;

/// @}

}; /* end BasicDart */
