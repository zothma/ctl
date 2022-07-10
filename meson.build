project('ctl','c')
configdep = dependency('libconfig')

inc = include_directories('include')
subdir('src')

executable('ctl', sources, include_directories : inc, dependencies: configdep)