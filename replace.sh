find ./decision_forests ! -path "./decision_forests/dataset/*" -type f -name "CMakeLists.txt" -exec sed -i "s/types$/dataset_types/g" {} \;
find ./decision_forests ! -path "./decision_forests/dataset/*" -type f -name "CMakeLists.txt" -exec sed -i "s/formats$/dataset_formats/g" {} \;
find ./decision_forests ! -path "./decision_forests/dataset/*" -type f -name "CMakeLists.txt" -exec sed -i "s/data_spec$/dataset_data_spec /g" {} \;
find ./decision_forests ! -path "./decision_forests/dataset/*" -type f -name "CMakeLists.txt" -exec sed -i "s/example_builder$/dataset_example_builder/g" {} \;
find ./decision_forests ! -path "./decision_forests/dataset/*" -type f -name "CMakeLists.txt" -exec sed -i "s/data_spec_inference$/dataset_data_spec_inference/g" {} \;
find ./decision_forests ! -path "./decision_forests/dataset/*" -type f -name "CMakeLists.txt" -exec sed -i "s/example_reader$/dataset_example_reader/g" {} \;
find ./decision_forests ! -path "./decision_forests/dataset/*" -type f -name "CMakeLists.txt" -exec sed -i "s/example_writer$/dataset_example_writer/g" {} \;
find ./decision_forests ! -path "./decision_forests/dataset/*" -type f -name "CMakeLists.txt" -exec sed -i "s/vertical_dataset$/dataset_vertical_dataset/g" {} \;
find ./decision_forests ! -path "./decision_forests/dataset/*" -type f -name "CMakeLists.txt" -exec sed -i "s/weight$/dataset_weight/g" {} \;
