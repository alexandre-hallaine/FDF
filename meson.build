project('FDF', 'c', version : '1.0.0')

cc = meson.get_compiler('c')

libm = cc.find_library('m')
libgnl = dependency('gnl')
libmlx = dependency('mlx')

src = files(
    'src/main.c',
    'src/map.c',
    'src/hook.c',
    'src/loop.c',
)

inc = include_directories('include')

executable('fdf', src,
           include_directories : inc,
           dependencies : [libm, libgnl, libmlx],
)
