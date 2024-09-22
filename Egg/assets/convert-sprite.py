from PIL import Image
import os
from pathlib import Path

def get_shade(rgba, shades, shade):
    w = (254 + shades) // shades
    b = (shade + 1) * w
    return 1 if rgba[0] >= b else 0

def get_mask(rgba):
    return 1 if rgba[3] >= 128 else 0

def convert(fname, shades, sw = None, sh = None, num = None, maskImage = False):

    if not (shades >= 2 and shades <= 4):
        print('shades argument must be 2, 3, or 4')
        return None

    im = Image.open(fname).convert('RGBA')
    pixels = list(im.getdata())
    
    masked = maskImage
    q = 0
    for i in pixels:
        q = q + 1
        # print(i[0])
        # print(i[1])
        # print(i[2])
        # print(i[3])
        if i[3] < 255:
            # print('masked!!! ')
            # print(q)
            masked = True
            # exit()
            break

    print('{}, shades {}, masked {}'.format(fname, shades, masked))


    w = im.width
    h = im.height
    if sw is None: sw = w
    if sh is None: sh = h
    nw = w // sw
    nh = h // sh
    if num is None: num = nw * nh
    sp = (sh + 7) // 8
    
    if nw * nh <= 0:
        print('%s: Invalid sprite dimensions' % fname)
        return None
        
    bytes = bytearray([sw, sh])
    
    for n in range(num):
        bx = (n % nw) * sw
        by = (n // nw) * sh
        for shade in range(shades - 1):
            for p in range(sp):
                for ix in range(sw):
                    x = bx + ix
                    byte = 0
                    mask = 0
                    for iy in range(8):
                        y = p * 8 + iy
                        if y >= sh: break
                        y += by
                        i = y * w + x
                        rgba = pixels[i]
                        byte |= (get_shade(rgba, shades, shade) << iy)
                        mask |= (get_mask(rgba) << iy)
                    bytes += bytearray([byte])
                    if masked:
                        bytes += bytearray([mask])
    
    return bytes
    
def convert_header(fname, fout, sym, shades, sw = None, sh = None, num = None, maskImage = False):
    bytes = convert(fname, shades, sw, sh, num, maskImage)
    if bytes is None: return
    with open(fout, 'a') as f:
        # f.write('#pragma once\n\n#include <stdint.h>\n#include <avr/pgmspace.h>\n\n')
        # f.write('constexpr uint8_t %s[] PROGMEM =\n{\n' % sym)
        f.write('uint8_t %s[] = {\n  ' % sym)
        for n in range(len(bytes)):
            if n % 16 == 2:
                f.write('\n  ')
            f.write('%3d,' % bytes[n])
            # f.write(' ' if n % 16 != 15 else '\n')
            # f.write(' ' if n % 18 != 2 else '\n')
            f.write(' ')
        if len(bytes) % 16 != 2:
            f.write('\n')
        f.write('};\n\n')

def deleteFile(filename):
    if os.path.isfile(filename):
        os.remove(filename)

BASE = '../'
IMAGES = '../images/'

deleteFile(BASE + 'Images.hpp')

#convert_header(IMAGES + 'PPOT.png', BASE + 'Images.hpp', 'PPOT', 4, 128, 64)

# add more images ..

convert_header(IMAGES + 'dpad_64x16.png', BASE + 'Images.hpp', 'dpad', 4, 16, 16)
convert_header(IMAGES + 'abutton_16x16.png', BASE + 'Images.hpp', 'abutton', 4, 16, 16)
convert_header(IMAGES + 'bbutton.png', BASE + 'Images.hpp', 'bbutton', 4, 16, 16)
convert_header(IMAGES + 'hydra.png', BASE + 'Images.hpp', 'hydraicon', 4, 16, 16)


convert_header(IMAGES + 'egg_56x64.png', BASE + 'Images.hpp', 'eggy', 4, 56, 64)
convert_header(IMAGES + 'hatching_56x64.png', BASE + 'Images.hpp', 'hatchingegg', 4, 56, 64)
convert_header(IMAGES + 'eggcon_16x16.png', BASE + 'Images.hpp', 'eggcon', 4, 16, 16)
convert_header(IMAGES + 'rottenegg_56x64.png', BASE + 'Images.hpp', 'badegg', 4, 56, 64)




convert_header(IMAGES + 'goopsphere_16x16.png', BASE + 'Images.hpp', 'goopsphere', 4, 16, 16)
convert_header(IMAGES + 'magmalionsphere_32x32.png', BASE + 'Images.hpp', 'magmalionsphere', 4, 32, 32)
convert_header(IMAGES + 'unagisphere_16x16.png', BASE + 'Images.hpp', 'unagisphere', 4, 16, 16)
convert_header(IMAGES + 'bunsphere_16x16.png', BASE + 'Images.hpp', 'bunsphere', 4, 16, 16)
convert_header(IMAGES + 'spikersphere_16x16.png', BASE + 'Images.hpp', 'spikersphere', 4, 16, 16)
convert_header(IMAGES + 'bugchimp.png', BASE + 'Images.hpp', 'chimpsphere', 4, 16, 16)
convert_header(IMAGES + 'cerberussphere.png', BASE + 'Images.hpp', 'puppysphere', 4, 16, 16)
convert_header(IMAGES + 'chickensphere_18x16.png', BASE + 'Images.hpp', 'hensphere', 4, 18, 16)
convert_header(IMAGES + 'crabsphere.png', BASE + 'Images.hpp', 'crabsphere', 4, 16, 16)
convert_header(IMAGES + 'frogsphere.png', BASE + 'Images.hpp', 'frogsphere', 4, 16, 16)
convert_header(IMAGES + 'devilgoatsphere.png', BASE + 'Images.hpp', 'goatsphere', 4, 32, 32)
convert_header(IMAGES + 'fishsphere.png', BASE + 'Images.hpp', 'fishsphere', 4, 16, 16)
convert_header(IMAGES + 'flamehorsesphere.png', BASE + 'Images.hpp', 'horsesphere', 4, 16, 16)
convert_header(IMAGES + 'frexsphere.png', BASE + 'Images.hpp', 'frexsphere', 4, 16, 16)
convert_header(IMAGES + 'harpysphere.png', BASE + 'Images.hpp', 'harpysphere', 4, 16, 16)
convert_header(IMAGES + 'bullsphere.png', BASE + 'Images.hpp', 'bullsphere', 4, 16, 16)
convert_header(IMAGES + 'hornetsphere.png', BASE + 'Images.hpp', 'hornetsphere', 4, 16, 16)
convert_header(IMAGES + 'hypnosphere.png', BASE + 'Images.hpp', 'hypnosphere', 4, 16, 16)
convert_header(IMAGES + 'lizardsphere.png', BASE + 'Images.hpp', 'lizardsphere', 4, 16, 16)
convert_header(IMAGES + 'octosphere.png', BASE + 'Images.hpp', 'octosphere', 4, 16, 16)
convert_header(IMAGES + 'shellysphere.png', BASE + 'Images.hpp', 'shellysphere', 4, 16, 16)
convert_header(IMAGES + 'snakesphere.png', BASE + 'Images.hpp', 'snakesphere', 4, 16, 16)
convert_header(IMAGES + 'tortoisesphere.png', BASE + 'Images.hpp', 'tortoisesphere', 4, 32, 32)






convert_header(IMAGES + 'bunnolio_32x32.png', BASE + 'Images.hpp', 'bun', 4, 32, 32)
convert_header(IMAGES + 'goop_32x32.png', BASE + 'Images.hpp', 'goop', 4, 32, 32)
convert_header(IMAGES + 'unagi.png', BASE + 'Images.hpp', 'unagi', 4, 32, 32)
convert_header(IMAGES + 'Spiker.png', BASE + 'Images.hpp', 'spiker', 4, 32, 32)
#convert_header(IMAGES + 'SunMeow.png', BASE + 'Images.hpp', 'sunmeow', 4, 28, 32)
#convert_header(IMAGES + 'ThundraDoe.png', BASE + 'Images.hpp', 'thundra', 4, 32, 31)
#convert_header(IMAGES + 'SpookyButterfly.png', BASE + 'Images.hpp', 'spookafly', 4, 31, 32)
#convert_header(IMAGES + 'Specter.png', BASE + 'Images.hpp', 'specter', 4, 32, 30)
#convert_header(IMAGES + 'SeaSpike.png', BASE + 'Images.hpp', 'seaspike', 4, 32, 32)
#convert_header(IMAGES + 'Rockaroo.png', BASE + 'Images.hpp', 'rockaroo', 4, 32, 32)
#convert_header(IMAGES + 'Rock Slime.png', BASE + 'Images.hpp', 'rslime', 4, 32, 31) #eh, this one sucks
convert_header(IMAGES + 'Octopus.png', BASE + 'Images.hpp', 'octo', 4, 32, 30)
convert_header(IMAGES + 'Metal Snake.png', BASE + 'Images.hpp', 'msnake', 4, 32, 32)
convert_header(IMAGES + 'Ladybird.png', BASE + 'Images.hpp', 'chicky', 4, 30, 32)
convert_header(IMAGES + 'Hypnotic Tapir.png', BASE + 'Images.hpp', 'hypnot', 4, 31, 31)
convert_header(IMAGES + 'Hornet.png', BASE + 'Images.hpp', 'hornet', 4, 32, 32)
convert_header(IMAGES + 'Heavens Bull.png', BASE + 'Images.hpp', 'bull', 4, 30, 32)
convert_header(IMAGES + 'Harpy.png', BASE + 'Images.hpp', 'harpy', 4, 32, 32)
convert_header(IMAGES + 'Fungusaurus Rex.png', BASE + 'Images.hpp', 'frex', 4, 31, 32)
convert_header(IMAGES + 'Flaming Stallion.png', BASE + 'Images.hpp', 'horsey', 4, 32, 32)
convert_header(IMAGES + 'Dread Carp.png', BASE + 'Images.hpp', 'fishy', 4, 32, 32)
convert_header(IMAGES + 'Death Frog.png', BASE + 'Images.hpp', 'froggy', 4, 32, 32)
convert_header(IMAGES + 'Cursed Shell.png', BASE + 'Images.hpp', 'shelly', 4, 32, 32)
convert_header(IMAGES + 'Claw King.png', BASE + 'Images.hpp', 'crab', 4, 32, 32)
convert_header(IMAGES + 'Cerberus.png', BASE + 'Images.hpp', 'puppy', 4, 28, 30)
convert_header(IMAGES + 'Baloonor.png', BASE + 'Images.hpp', 'lizard', 4, 32, 32)
convert_header(IMAGES + 'Bug Chimp.png', BASE + 'Images.hpp', 'chimp', 4, 32, 32)

convert_header(IMAGES + 'magmalionripplesspritesheet_64x64.png', BASE + 'Images.hpp', 'magmalion', 4, 64, 64)
convert_header(IMAGES + 'DevilGoat_64x64.png', BASE + 'Images.hpp', 'goat', 4, 64, 64)
convert_header(IMAGES + 'Adamantoise_64x64.png', BASE + 'Images.hpp', 'tortoise', 4, 63, 64)
convert_header(IMAGES + 'DGoatSpritesheet.png', BASE + 'Images.hpp', 'goatwiggle', 4, 64, 64)





