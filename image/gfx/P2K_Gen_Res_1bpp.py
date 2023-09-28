#!/usr/bin/env python

"""
Generate C-like headers from BMP 1bpp sprites.

python -m pip install --upgrade pip
python -m pip install --upgrade Pillow
"""

import os
import sys

import PIL
from PIL import Image

bmp_offset = 0x0A
out = 'P2K_GFX_Bitmaps.h'
files = [
	'P2K_Frame_23x23.bmp',
	'P2K_Frame_36x36.bmp',
	'P2K_Numbers_231x21.bmp',
	'P2K_Numbers_352x32.bmp',
]

def generate_c_resource_header(filename):
	bmp_temp = 'temp_' + filename
	bmp_flip = Image.open(filename).transpose(PIL.Image.FLIP_TOP_BOTTOM)
	bmp_flip.save(bmp_temp)

	with open(bmp_temp, 'rb') as file_in, open(out, 'a') as file_out:
		file_in.seek(bmp_offset)
		data_offset = int.from_bytes(file_in.read(1))

		file_in.seek(data_offset)
		rev_buff = bytes(file_in.read())

		filename = filename.replace('.', '_')
		size_w = filename.split('_')[2].split('x')[0]
		size_h = filename.split('_')[2].split('x')[1]

		file_out.write('static const UINT32 ' + filename + '_width = ' + size_w + ';\n')
		file_out.write('static const UINT32 ' + filename + '_height = ' + size_h + ';\n')
		file_out.write('static const UINT32 ' + filename + '_size = ' + str(len(rev_buff)) + ';\n')

		file_out.write('static const UINT8 ' + filename + '[] = {\n')

		i = 0
		size = 0
		for byte in rev_buff:
			if i == 0:
				file_out.write('\t')
			file_out.write(f'0x{byte:02X}')
			if size != (len(rev_buff) - 1):
				if i == 0x0F:
					file_out.write(',')
				else:
					file_out.write(', ')
			i += 1
			if i > 0x0F and size != (len(rev_buff) - 1):
				file_out.write('\n')
				i = 0
			size += 1

		file_out.write('\n};\n\n')

	if os.path.exists(bmp_temp):
		os.remove(bmp_temp)

if __name__ == '__main__':
	if os.path.exists(out):
		os.remove(out)
	for filename in files:
		generate_c_resource_header(filename)
