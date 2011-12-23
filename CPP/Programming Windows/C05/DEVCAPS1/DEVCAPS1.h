#define DevCapsNumber (sizeof(devcaps) / sizeof(devcaps[0]))
struct
{
    int INDEX;
    TCHAR *szLabel;
    TCHAR *szDesc;
}
devcaps[] =
{
    DRIVERVERSION, TEXT( "DRIVERVERSION"),TEXT( "Device driver version"),
    TECHNOLOGY, TEXT( "TECHNOLOGY"),TEXT( "Device classification"),
    HORZSIZE, TEXT( "HORZSIZE"),TEXT( "Horizontal size in millimeters"),
    VERTSIZE, TEXT( "VERTSIZE"),TEXT( "Vertical size in millimeters"),
    HORZRES, TEXT( "HORZRES"),TEXT( "Horizontal width in pixels"),
    VERTRES, TEXT( "VERTRES"),TEXT( "Vertical height in pixels"),
    BITSPIXEL, TEXT( "BITSPIXEL"),TEXT( "Number of bits per pixel"),
    PLANES, TEXT( "PLANES"),TEXT( "Number of planes"),
    NUMBRUSHES, TEXT( "NUMBRUSHES"),TEXT( "Number of brushes the device has"),
    NUMPENS, TEXT( "NUMPENS"),TEXT( "Number of pens the device has"),
    NUMMARKERS, TEXT( "NUMMARKERS"),TEXT( "Number of markers the device has"),
    NUMFONTS, TEXT( "NUMFONTS"),TEXT( "Number of fonts the device has"),
    NUMCOLORS, TEXT( "NUMCOLORS"),TEXT( "Number of colors the device supports"),
    PDEVICESIZE, TEXT( "PDEVICESIZE"),TEXT( "Size required for device descriptor"),
    CURVECAPS, TEXT( "CURVECAPS"),TEXT( "Curve capabilities"),
    LINECAPS, TEXT( "LINECAPS"),TEXT( "Line capabilities"),
    POLYGONALCAPS, TEXT( "POLYGONALCAPS"),TEXT( "Polygonal capabilities"),
    TEXTCAPS, TEXT( "TEXTCAPS"),TEXT( "Text capabilities"),
    CLIPCAPS, TEXT( "CLIPCAPS"),TEXT( "Clipping capabilities"),
    RASTERCAPS, TEXT( "RASTERCAPS"),TEXT( "Bitblt capabilities"),
    ASPECTX, TEXT( "ASPECTX"),TEXT( "Length of the X leg"),
    ASPECTY, TEXT( "ASPECTY"),TEXT( "Length of the Y leg"),
    ASPECTXY, TEXT( "ASPECTXY "),TEXT( "Length of the hypotenuse")
};
