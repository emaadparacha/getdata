// getdata library
mod getdata;
use getdata::DirFile;
mod getdata_bindings; // Declare the bindings module

fn main() {
    // New Code

    let dirfile = DirFile::new("/data/flights/superbit_2023/timestreams/master_2023-05-03-07-24-30");

    // Get the number of fields in the dirfile
    let nfields = dirfile.nfields();
    println!("nfields: {:?}", nfields);

    // Get the number of frames in the dirfile
    let total_frames = dirfile.nframes();
    println!("Total frames: {:?}", total_frames);

    // Get samples per frame for "lon"
    let samples_per_frame = dirfile.spf("lon");
    println!("Samples per frame for lon: {:?}", samples_per_frame);

    // Get the type of the field "lon"
    let lon_type = dirfile.field_type("lon");
    println!("lon_type: {:?}", lon_type);

    // Get the data of the field "lon"
    let lon_data = dirfile.get_data("lon");
    // Print the size
    println!("lon_data size: {:?}", lon_data.len());

    // Print the last 15 elements of the vector (or as many as available)
    let to_print = lon_data.iter().skip(lon_data.len() - 15);
    for (i, value) in to_print.enumerate() {
        println!("lon_data[{}]: {:?}", i + lon_data.len() - 15, value);
    }

    // Get data of the field "lat"
    let lat_data = dirfile.get_data("lat");
    // Print the size
    println!("lat_data size: {:?}", lat_data.len());

    // Print the last 15 elements of the vector (or as many as available)
    let to_print = lat_data.iter().skip(lat_data.len() - 15);
    for (i, value) in to_print.enumerate() {
        println!("lat_data[{}]: {:?}", i + lat_data.len() - 15, value);
    }

    // Get the data of the field "file_chunk_downlink"
    let file_chunk_downlink_data = dirfile.get_data("file_chunk_downlink");
    // Print the size
    println!("file_chunk_downlink_data size: {:?}", file_chunk_downlink_data.len());

    // Print the last 15 elements of the vector (or as many as available)
    let to_print = file_chunk_downlink_data.iter().skip(file_chunk_downlink_data.len() - 15);
    for (i, value) in to_print.enumerate() {
        println!("file_chunk_downlink_data[{}]: {:?}", i + file_chunk_downlink_data.len() - 15, value);
    }

    // Do the same for the field "cent_est_x_fsc2"
    let cent_est_x_fsc2_data = dirfile.get_data("cent_est_x_fsc2");
    // Print the size
    println!("cent_est_x_fsc2_data size: {:?}", cent_est_x_fsc2_data.len());

    // Print the last 15 elements of the vector (or as many as available)
    let to_print = cent_est_x_fsc2_data.iter().skip(cent_est_x_fsc2_data.len() - 15);
    for (i, value) in to_print.enumerate() {
        println!("cent_est_x_fsc2_data[{}]: {:?}", i + cent_est_x_fsc2_data.len() - 15, value);
    }

}
