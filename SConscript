from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add sgm706 src files.
if GetDepend('PKG_USING_SGM706'):
    src += Glob('src/sgm706.c')

if GetDepend('PKG_USING_SGM706_SAMPLE'):
    src += Glob('examples/sgm706_sample.c')

# add sgm706 include path.
path  = [cwd + '/inc']

# add src and include to group.
group = DefineGroup('sgm706', src, depend = ['PKG_USING_SGM706'], CPPPATH = path)

Return('group')
