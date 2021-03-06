/* -------------------------------------------------------------------------------

   Copyright (C) 1999-2007 id Software, Inc. and contributors.
   For a list of contributors, see the accompanying CONTRIBUTORS file.

   This file is part of GtkRadiant.

   GtkRadiant is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   GtkRadiant is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GtkRadiant; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

   -------------------------------------------------------------------------------

   This code has been altered significantly from its original form, to support
   several games based on the Quake III Arena engine, in the form of "Q3Map2."

   ------------------------------------------------------------------------------- */



/* dependencies */
#include "q3map2.h"



struct HelpOption
{
	const char* name;
	const char* description;
};

void HelpOptions(const char* group_name, int indentation, int width, struct HelpOption* options, int count)
{
	indentation *= 2;
	char* indent = malloc(indentation+1);
	memset(indent, ' ', indentation);
	indent[indentation] = 0;
	printf("%s%s:\n", indent, group_name);
	indentation += 2;
	indent = realloc(indent, indentation+1);
	memset(indent, ' ', indentation);
	indent[indentation] = 0;

	int i;
	for ( i = 0; i < count; i++ )
	{
		int printed = printf("%s%-24s  ", indent, options[i].name);
		int descsz = strlen(options[i].description);
		int j = 0;
		while ( j < descsz && descsz-j > width - printed )
		{
			if ( j != 0 )
				printf("%s%26c",indent,' ');
			int fragment = width - printed;
			while ( fragment > 0 && options[i].description[j+fragment-1] != ' ')
					fragment--;
			j += fwrite(options[i].description+j, sizeof(char), fragment, stdout);
			putchar('\n');
			printed = indentation+26;
		}
		if ( j == 0 )
		{
			printf("%s\n",options[i].description+j);
		}
		else if ( j < descsz )
		{
			printf("%s%26c%s\n",indent,' ',options[i].description+j);
		}
	}

	putchar('\n');

	free(indent);
}

void HelpBsp()
{
	struct HelpOption bsp[] = {
		{"-bsp <filename.map>", "Switch that enters this stage (this is the default)"},
		{"-altsplit", "Alternate BSP tree splitting weights (should give more fps)"},
		{"-bspfile <filename.bsp>", "BSP file to write"},
		{"-celshader <shadername>", "Set the global cel shader name"},
		{"-custinfoparms", "Read scripts/custinfoparms.txt"},
		{"-de <F>", "Distance epsilon for plane snapping, etc."},
		{"-debuginset", "Push all triangle vertexes towards the triangle center"},
		{"-debugportals", "Make BSP portals visible in the map (needs q3map.shader)"},
		{"-debugsurfaces", "Color the vertexes according to the index of the surface (needs q3map.shader)"},
		{"-deep", "Use detail brushes in the BSP tree, but at lowest priority (should give more fps)"},
		{"-fakemap", "Write fakemap.map containing all world brushes"},
		{"-flares", "Turn on support for flares (TEST?)"},
		{"-flat", "Enable flat shading (good for combining with -celshader)"},
		{"-fulldetail", "Treat detail brushes as structural ones"},
		{"-keeplights", "Keep light entities in the BSP file after compile"},
		{"-leaktest", "Abort if a leak was found"},
		{"-linfile <filename.lin>", "Line file to write"},
		{"-maxarea", "Select more GPU friendly face surface splitting algorithm (should give more fps)"},
		{"-meta", "Combine adjacent triangles of the same texture to surfaces (ALWAYS USE THIS)"},
		{"-metaadequatescore <N>", "Set ADEQUATE meta score"},
		{"-metagoodscore <N>", "Set GOOD meta score"},
		{"-metamaxbboxdistance <F>", "Set meta maximum bounding box distance"},
		{"-mi <N>", "Set the maximum number of indexes per surface"},
		{"-minsamplesize <N>", "Set minimum lightmap resolution in luxels/qu"},
		{"-mv <N>", "Set the maximum number of vertices of a lightmapped surface"},
		{"-ne <F>", "Normal epsilon for plane snapping, etc."},
		{"-nocurves", "Turn off support for patches"},
		{"-nodetail", "Leave out detail brushes"},
		{"-noflares", "Turn off support for flares"},
		{"-nofog", "Turn off support for fog volumes"},
		{"-nohint", "Turn off support for hint brushes"},
		{"-nosRGB", "Set all colorspaces to linear"},
		{"-nosRGBcolor", "Set _color colorspace to linear"},
		{"-nosRGBtex", "Set texture colorspace to linear"},
		{"-nosubdivide", "Turn off support for `q3map_tessSize` (breaks water vertex deforms)"},
		{"-notjunc", "Do not fix T-junctions (causes cracks between triangles, do not use)"},
		{"-nowater", "Turn off support for liquids (water, slime and lava)"},
		{"-np <F>", "Force all surfaces to be nonplanar with a given shade angle"},
		{"-onlyents", "Only update entities in the BSP"},
		{"-patchmeta", "Turn patches into triangle meshes for display"},
		{"-prtfile <filename.prt>", "Portal file to write"},
		{"-rename", "Append suffix to miscmodel shaders (needed for SoF2)"},
		{"-samplesize <N>", "Set default lightmap resolution in luxels/qu"},
		{"-sRGBcolor", "Set _color colorspace to sRGB"},
		{"-sRGBtex", "Set texture colorspace to sRGB"},
		{"-skyfix", "Turn sky box into six surfaces to work around ATI problems (in 2003)"},
		{"-snap <N>", "Snap brush bevel planes to the given number of units"},
		{"-srffile <filename.srf>", "Surface file to write"},
		{"-tempname <filename.map>", "Read a temporary MAP file and then delete it"},
		{"-texrange <N>", "Limit per-surface texture range to the given number of units, and subdivide surfaces like with `q3map_tessSize` if this is not met"},
		{"-tmpout", "Write the BSP file to /tmp (NOT WORKING!)"},
		{"-verboseentities", "Enable `-v` only for map entities, not for the world"},
	};
	HelpOptions("BSP Stage", 0, 80, bsp, sizeof(bsp)/sizeof(struct HelpOption));
}

void HelpVis()
{
	struct HelpOption vis[] = {
		{"-vis <filename.map>", "Switch that enters this stage"},
		{"-fast", "Very fast and crude vis calculation"},
		{"-merge", "Faster but still okay vis calculation"},
		{"-mergeportals", "The less crude half of `-merge`, makes vis sometimes much faster but doesn't hurt fps usually"},
		{"-nopassage", "Just use PortalFlow vis (usually less fps)"},
		{"-nosort", "Do not sort the portals before calculating vis (usually slower)"},
		{"-passageOnly", "Just use PassageFlow vis (usually less fps)"},
		{"-prtfile <filename.prt>", "Portal file to read"},
		{"-saveprt", "Keep the Portal file after running vis (so you can run vis again)"},
		{"-tmpin", "Use /tmp folder for input"},
		{"-tmpout", "Use /tmp folder for output"},
	};
	HelpOptions("VIS Stage", 0, 80, vis, sizeof(vis)/sizeof(struct HelpOption));
}

void HelpLight()
{
	struct HelpOption light[] = {
		{"-light <filename.map>", "Switch that enters this stage"},
		{"-vlight <filename.map>", "Deprecated alias for `-light -fast` ... filename.map"},
		{"-approx <N>", "Vertex light approximation tolerance (never use in conjunction with deluxemapping)"},
		{"-areascale <F, `-area` F>", "Scaling factor for area lights (surfacelight)"},
		{"-border", "Add a red border to lightmaps for debugging"},
		{"-bounce <N>", "Number of bounces for radiosity"},
		{"-bouncegrid", "Also compute radiosity on the light grid"},
		{"-bounceonly", "Only compute radiosity"},
		{"-bouncescale <F>", "Scaling factor for radiosity"},
		{"-bspfile <filename.bsp>", "BSP file to write"},
		{"-cheap", "Abort vertex light calculations when white is reached"},
		{"-cheapgrid", "Use `-cheap` style lighting for radiosity"},
		{"-compensate <F>", "Lightmap compensate (darkening factor applied after everything else)"},
		{"-cpma", "CPMA vertex lighting mode"},
		{"-custinfoparms", "Read scripts/custinfoparms.txt"},
		{"-dark", "Darken lightmap seams"},
		{"-debug", "Mark the lightmaps according to the cluster: unmapped clusters get yellow, occluded ones get pink, flooded ones get blue overlay color, otherwise red"},
		{"-debugaxis", "Color the lightmaps according to the lightmap axis"},
		{"-debugcluster", "Color the lightmaps according to the index of the cluster"},
		{"-debugdeluxe", "Show deluxemaps on the lightmap"},
		{"-debugnormals", "Color the lightmaps according to the direction of the surface normal"},
		{"-debugorigin", "Color the lightmaps according to the origin of the luxels"},
		{"-debugsurfaces, -debugsurface", "Color the lightmaps according to the index of the surface"},
		{"-debugunused", "This option does nothing"},
		{"-deluxe, -deluxemap", "Enable deluxemapping (light direction maps)"},
		{"-deluxemode 0", "Use modelspace deluxemaps (DarkPlaces)"},
		{"-deluxemode 1", "Use tangentspace deluxemaps"},
		{"-dirtdebug, -debugdirt", "Store the dirtmaps as lightmaps for debugging"},
		{"-dirtdepth", "Dirtmapping depth"},
		{"-dirtgain", "Dirtmapping exponent"},
		{"-dirtmode 0", "Ordered direction dirtmapping"},
		{"-dirtmode 1", "Randomized direction dirtmapping"},
		{"-dirtscale", "Dirtmapping scaling factor"},
		{"-dirty", "Enable dirtmapping"},
		{"-dump", "Dump radiosity from `-bounce` into numbered MAP file prefabs"},
		{"-export", "Export lightmaps when compile finished (like `-export` mode)"},
		{"-exposure <F>", "Lightmap exposure to better support overbright spots"},
		{"-external", "Force external lightmaps even if at size of internal lightmaps"},
		{"-extra", "Deprecated alias for `-super 2`"},
		{"-extravisnudge", "Broken feature to nudge the luxel origin to a better vis cluster"},
		{"-extrawide", "Deprecated alias for `-super 2 -filter`"},
		{"-fastallocate", "Use `-fastallocate` to trade lightmap size against allocation time (useful with hi res lightmaps on large maps: reduce allocation time from days to minutes for only some extra bytes)"},
		{"-fastbounce", "Use `-fast` style lighting for radiosity"},
		{"-faster", "Use a faster falloff curve for lighting; also implies `-fast`"},
		{"-fastgrid", "Use `-fast` style lighting for the light grid"},
		{"-fast", "Ignore tiny light contributions"},
		{"-filter", "Lightmap filtering"},
		{"-floodlight", "Enable floodlight (zero-effort somewhat decent lighting)"},
		{"-gamma <F>", "Lightmap gamma"},
		{"-gridambientscale <F>", "Scaling factor for the light grid ambient components only"},
		{"-gridscale <F>", "Scaling factor for the light grid only"},
		{"-lightmapdir <directory>", "Directory to store external lightmaps (default: same as map name without extension)"},
		{"-lightmapsize <N>", "Size of lightmaps to generate (must be a power of two)"},
		{"-lomem", "Low memory but slower lighting mode"},
		{"-lowquality", "Low quality floodlight (appears to currently break floodlight)"},
		{"-minsamplesize <N>", "Set minimum lightmap resolution in luxels/qu"},
		{"-nocollapse", "Do not collapse identical lightmaps"},
		{"-nodeluxe, -nodeluxemap", "Disable deluxemapping"},
		{"-nogrid", "Disable grid light calculation (makes all entities fullbright)"},
		{"-nolightmapsearch", "Do not optimize lightmap packing for GPU memory usage (as doing so costs fps)"},
		{"-normalmap", "Color the lightmaps according to the direction of the surface normal (TODO is this identical to `-debugnormals`?)"},
		{"-nostyle, -nostyles", "Disable support for light styles"},
		{"-nosurf", "Disable tracing against surfaces (only uses BSP nodes then)"},
		{"-notrace", "Disable shadow occlusion"},
		{"-novertex", "Disable vertex lighting"},
		{"-patchshadows", "Cast shadows from patches"},
		{"-pointscale <F, `-point` F>", "Scaling factor for point lights (light entities)"},
		{"-q3", "Use nonlinear falloff curve by default (like Q3A)"},
		{"-samplescale <F>", "Scales all lightmap resolutions"},
		{"-samplesize <N>", "Sets default lightmap resolution in luxels/qu"},
		{"-samples <N>", "Adaptive supersampling quality"},
		{"-scale <F>", "Scaling factor for all light types"},
		{"-shadeangle <A>", "Angle for phong shading"},
		{"-shade", "Enable phong shading at default shade angle"},
		{"-skyscale <F, `-sky` F>", "Scaling factor for sky and sun light"},
		{"-smooth", "Deprecated alias for `-samples 2`"},
		{"-srffile <filename.srf>", "Surface file to read"},
		{"-style, -styles", "Enable support for light styles"},
		{"-sunonly", "Only compute sun light"},
		{"-super <N, `-supersample` N>", "Ordered grid supersampling quality"},
		{"-thresh <F>", "Triangle subdivision threshold"},
		{"-trianglecheck", "Broken check that should ensure luxels apply to the right triangle"},
		{"-trisoup", "Convert brush faces to triangle soup"},
		{"-wolf", "Use linear falloff curve by default (like W:ET)"},
	};

	HelpOptions("Light Stage", 0, 80, light, sizeof(light)/sizeof(struct HelpOption));
}

void HelpAnalyze()
{
	struct HelpOption analyze[] = {
		{"-analyze <filename.bsp>", "Switch that enters this mode"},
		{"-lumpswap", "Swap byte order in the lumps"},
	};

	HelpOptions("Analyze a BSP-like file structure", 0, 80, analyze, sizeof(analyze)/sizeof(struct HelpOption));
}

void HelpScale()
{
	struct HelpOption scale[] = {
		{"-scale <F> <filename.bsp>", "Switch that enters this mode"},
		{"-scale <FX FY FZ> <filename.bsp>", "Switch that enters this mode (non-uniform scale)"},
		{"-spawn_ref <F>", "Reference point in spawnpoints (info_player* entities)"},
		{"-tex", "Scale textures as well (disable texture lock)"},
	};
	HelpOptions("Scale a BSP file", 0, 80, scale, sizeof(scale)/sizeof(struct HelpOption));
}

void HelpConvert()
{
	struct HelpOption convert[] = {
		{"-convert <filename.bsp>", "Switch that enters this mode"},
		{"-de <F>", "Distance epsilon"},
		{"-deluxemapsastexcoord", "Extract deluxemap UV"},
		{"-format <ase|obj|map|map_bp>", "Select the converter (also a game name)"},
		{"-lightmapsastexcoord", "Extract lightmap UV"},
		{"-meta", "Force -meta in the BSP conversion"},
		{"-ne <F>", "Normal epsilon"},
		{"-patchmeta", "Force -patchmeta in the BSP conversion"},
		{"-readbsp", "Force reading a BSP file (default)"},
		{"-readmap", "Force reading a MAP file"},
		{"-shadersasbitmap", "Write shader names as \\*BITMAP/map_Kd keys to make prefabs (ase/obj only)"},
	};

	HelpOptions("Convert/Decompile", 0, 80, convert, sizeof(convert)/sizeof(struct HelpOption));
}

void HelpExport()
{
	struct HelpOption exportl[] = {
		{"-export <filename.bsp>", "Switch that enters this mode"}
	};

	HelpOptions("Export lightmaps from BSP", 0, 80, exportl, sizeof(exportl)/sizeof(struct HelpOption));
}

void HelpExportEnts()
{
	struct HelpOption exportents[] = {
		{"-exportents <filename.bsp>", "Switch that enters this mode"},
	};
	HelpOptions("Export entities from BSP", 0, 80, exportents, sizeof(exportents)/sizeof(struct HelpOption));
}

void HelpFixaas()
{
	struct HelpOption fixaas[] = {
		{"-fixaas <filename.bsp>", "Switch that enters this mode"},
	};

	HelpOptions("Fix AAS checksum", 0, 80, fixaas, sizeof(fixaas)/sizeof(struct HelpOption));
}

void HelpInfo()
{
	struct HelpOption info[] = {
		{"-info <filename.bsp>", "Switch that enters this mode"},
	};

	HelpOptions("Get info about a BSP file", 0, 80, info, sizeof(info)/sizeof(struct HelpOption));
}

void HelpImport()
{
	struct HelpOption import[] = {
		{"-import <filename.bsp>", "Switch that enters this mode"},
	};

	HelpOptions("Import lightmaps into BSP", 0, 80, import, sizeof(import)/sizeof(struct HelpOption));
}

void HelpMinimap()
{
	struct HelpOption minimap[] = {
		{"-minimap <filename.bsp>", "Switch that enters this mode"},
		{"-black", "Write the minimap as a black-on-transparency RGBA32 image"},
		{"-boost <F>", "Sets the contrast boost value (higher values make a brighter image); contrast boost is somewhat similar to gamma, but continuous even at zero"},
		{"-border <F>", "Sets the amount of border pixels relative to the total image size"},
		{"-gray", "Write the minimap as a white-on-black GRAY8 image"},
		{"-keepaspect", "Ensure the aspect ratio is kept (the minimap is then letterboxed to keep aspect)"},
		{"-minmax <xmin ymin zmin xmax ymax zmax>", "Forces specific map dimensions (note: the minimap actually uses these dimensions, scaled to the target size while keeping aspect with centering, and 1/64 of border appended to all sides)"},
		{"-nokeepaspect", "Do not ensure the aspect ratio is kept (makes it easier to use the image in your code, but looks bad together with sharpening)"},
		{"-o <filename.tga>", "Sets the output file name"},
		{"-random <N>", "Sets the randomized supersampling count (cannot be combined with `-samples`)"},
		{"-samples <N>", "Sets the ordered supersampling count (cannot be combined with `-random`)"},
		{"-sharpen <F>", "Sets the sharpening coefficient"},
		{"-size <N>", "Sets the width and height of the output image"},
		{"-white", "Write the minimap as a white-on-transparency RGBA32 image"},
	};

	HelpOptions("Create a minimap", 0, 80, minimap, sizeof(minimap)/sizeof(struct HelpOption));
}

void HelpCommon()
{
	struct HelpOption common[] = {
		{"-connect <address>", "Talk to a NetRadiant instance using a specific XML based protocol"},
		{"-force", "Allow reading some broken/unsupported BSP files e.g. when decompiling, may also crash"},
		{"-fs_basepath <path>", "Specify the main game directory path (can be used more than once)"},
		{"-fs_custompath <path>", "Specify an additional custom path (can be used more than once)"},
		{"-fs_forbiddenpath <pattern>", "Ignore all paths whose last dir matches with pattern (can be used more than once)"},
		{"-fs_game <dir>", "Specify an additional game directory name (i.e. baseq3, can be used more than once)"},
		{"-fs_home <path>", "Specify the user home directory (i.e. /home/user)"},
		{"-fs_homebase <dir>", "Specify the user game directory name (i.e. .q3a)"},
		{"-fs_homepath <path>", "Specify the user game directory path (i.e. /home/user/.q3a)"},
		{"-fs_pakpath <path>", "Same as -fs_custompath"},
		{"-game <gamename>", "Load settings for the given game (default to quake3)"},
		{"-subdivisions <N>", "Patch subdivisions tolerance (for -patchmeta, etc.)"},
		{"-threads <N>", "Number of threads to use"},
		{"-v", "Verbose mode"}
	};

	HelpOptions("Common Options", 0, 80, common, sizeof(common)/sizeof(struct HelpOption));

}

void HelpMain(const char* arg)
{
	printf("Usage: q3map2 [stage] [common options...] [stage options...] [stage source file]\n");
	printf("       q3map2 -help [stage]\n\n");

	HelpCommon();

	struct HelpOption stages[] = {
		{"-bsp", "BSP Stage"},
		{"-vis", "VIS Stage"},
		{"-light", "Light Stage"},
		{"-analyze", "Analyze a BSP-like file structure"},
		{"-convert", "Convert/Decompile"},
		{"-export", "Export lightmaps from BSP"},
		{"-exportents", "Export entities from BSP"},
		{"-fixaas", "Fix AAS checksum"},
		{"-import", "Import lightmaps into BSP"},
		{"-info", "Get info about a BSP file"},
		{"-minimap", "Create a minimap"},
		{"-scale", "Scale a BSP file"},
	};
	void(*help_funcs[])() = {
		HelpBsp,
		HelpVis,
		HelpLight,
		HelpAnalyze,
		HelpConvert,
		HelpExport,
		HelpExportEnts,
		HelpFixaas,
		HelpImport,
		HelpInfo,
		HelpMinimap,
		HelpScale,
	};

	if ( arg && strlen(arg) > 0 )
	{
		if ( arg[0] == '-' )
			arg++;

		unsigned i;
		for ( i = 0; i < sizeof(stages)/sizeof(struct HelpOption); i++ )
			if ( strcmp(arg, stages[i].name+1) == 0 )
			{
				help_funcs[i]();
				return;
			}
	}

	HelpOptions("Stages", 0, 80, stages, sizeof(stages)/sizeof(struct HelpOption));
}
