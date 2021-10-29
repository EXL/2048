2048-MotoMAGX
=============

Project files for the [MOTODEV Studio for Linux v0.3.0](https://motofan.ru/files/soft/MOTODEV_Studio.zip) IDE.

## Debug build

1. Run "MOTODEV Studio for Linux v0.3.0" IDE.
2. Select "File" => "Import..." => "Existing Projects into Workspace" then click "Next" button.
3. Click "Browse..." button and select "2048/2048-MotoMAGX/MotoDevStudioProject/2048-MotoMAGX/" directory.
4. Click "Finish" button.
5. Select "Project" => "Build All" for building Debug project.

## Release build

1. Select "2048-MotoMAGX" directory in the "Project Explorer".
2. Select "Project" => "Properties" and then select "C/C++ Build" item.
3. Click "Manage configurations" button, select "MOTOMAGX_0.3_x86_Release" configuration.
4. Click "Set Active" button, then click "OK" button twice.
5. Select "Project" => "Build All" for building Release project.

## Export MPKG-package

1. Select "File" => "Export..." => "MOTODEV Studio" => "MOTODEV Studio Package (MPKG)" then click "Next" button.
2. Select all package descriptors then click "Finish" button.
3. Get ready-to-install MPKG packages in the "2048/2048-MotoMAGX/MotoDevStudioProject/2048-MotoMAGX/dist/" directory.

## Run on MotoMAGX Emulator

1. Select "Run" => "Run" => "MOTODEV Appliction" choose Release package descriptor.
2. Click "Run" button and then click "OK" twice.

## Additional Information

See [MOTODEV Studio for Linux - Preview v0.3 | Эмулятор и несостоявшееся IDE для MotoMAGX](https://forum.motofan.ru/index.php?showtopic=150504) (in Russian) thread on the MotoFan.Ru forum.
