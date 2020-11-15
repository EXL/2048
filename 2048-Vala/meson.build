project('2048-Vala', 'vala', 'c', version: '1.0.0')

srcs = files('../src/2048.c', 'EngineWrapper.c', '2048-Vala.vala')
incs = include_directories('../src/')
deps = [ dependency('gtk+-3.0') ]

executable(meson.project_name(), srcs, include_directories: incs, dependencies: deps, install: true)

