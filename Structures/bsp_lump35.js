/*enum GameLumpID : int
{
	// All of them had the prefix ''STATIC_PROP_" and I abbreivated it
	//// All the ID chars are in a reverse order, read them in the correct endian order
	GL_STATIC_PROPS = 1936749168, // "prps"
	GL_DETAIL_PROPS = 1685090928, // "prpd"
	GL_DETAIL_PROP_LIGHTING = 1685089396, // "tlpd"
	GL_DETAIL_PROP_LIGHTING_HDR = 1685089384, // "hlpd"
};*/
function tostring_GameLumpID( chararray )
{
	let newstring = ""
	for (let i = 0; i < chararray.length; i++)
		newstring = newstring + chararray[i]

	switch( newstring )
	{
		case "prps":
			return "GAMELUMP_STATIC_PROPS"
		case "prpd":
			return "GAMELUMP_DETAIL_PROPS"
		case "tlpd":
			return "GAMELUMP_DETAIL_PROP_LIGHTING"
		case "hlpd":
			return "GAMELUMP_DETAIL_PROP_LIGHTING_HDR"
	}
}
/*
function ModelPathToName( chararray )
{
	let newstring = ""
	for (let i = 0; i < chararray.length; i++)
	{
		if( chararray[i] != 0 )
			newstring = newstring + chararray[i]
		else
			break
	}

	let newstring_split = newstring.split("/")
	return newstring_split[newstring_split.length-1]
}*/
