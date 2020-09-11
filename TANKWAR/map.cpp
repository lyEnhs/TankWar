
#include"StdAfx.h"
#include"map.h"
#include"DrawTools.h"
#include"score.h"

extern CScore     g_score;
extern CDBBuffer buffer;
extern CDrawTools g_cdrawtools;

Cmap::Cmap() 
{
	//	  
}
Cmap::~Cmap()
{
	//
 }
void Cmap::Initmap(bool read)
{

	 FILE *fp;
	 if(!read)
	 {
		if ( (fopen_s(&fp, "CMap.txt","rb") ) != 0 )
		{
			exit(1);
		}
	 }
	 else
	{
		if ( (fopen_s(&fp, "Level2.txt","rb") ) != 0 )
		{
			exit(1); 
		}

	}
	Smap *ip = &m_map[0][0];
	int index = 0;

	char ch = 0;
	char data[16] =" ";

	int ibegin = 0 ;
	int iend = 0;

	ch = fgetc(fp);

	while( ch != EOF )
	{
		if( ch == ',')
		{
			iend = ftell( fp ) - 1 ;
			int isize = iend-ibegin ;
			fseek( fp,ibegin,SEEK_SET );
			fread( data,isize,1,fp );
			data[isize] ='\0';
			ip[index].ID = atoi(data );
			int x = index%16;
			int y = index/16;
			ip[index].rt.left  =x*32;
			ip[index].rt.top   =y*32;
			ip[index].rt.right =x*32+32;
			ip[index].rt.bottom=y*32+32;
			index++;
			ibegin = iend + 1;
			fseek( fp,ibegin,SEEK_SET );
		}

		ch = fgetc( fp ) ;
	}
	fclose(fp);
 }


void Cmap::Render()
{
for(int i = 0 ;i<16;i++)
{
	for(int j=0;j<16;j++)
	{
		switch( m_map[i][j].ID )
		{
			case 1:
				g_cdrawtools.Render("brick",j*32,i*32);
			break;

			case 2:
				 g_cdrawtools.Render("water",j*32,i*32);
			break;

			case 3:
				 g_cdrawtools.Render("gangzhuan",j*32,i*32);
			break;

			case 5:
				g_cdrawtools.Render("boss",j*32+6,i*32+6);
				break;

			default:
				break;
							
			}

		}
	}
}
void Cmap::RenderGrass()
{
	for(int i = 0 ;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			switch( m_map[i][j].ID )
			{
				case 4:
					g_cdrawtools.Render("grass",j*32,i*32,0,0,32,32);
				break;
			}

		}
	}
}