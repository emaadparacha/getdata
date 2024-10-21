use rustygetdata::Dirfile;

fn main() {
    let my_dirfile = Dirfile::new("/data/flights/superbit_2023/timestreams/master_2023-05-03-07-24-30");

    println!("Number of fields: {}", my_dirfile.nfields());
    println!("Number of frames: {}", my_dirfile.nframes());
    
    let data = my_dirfile.get_data("lon");

    // Print the first 15 elements of the data
    println!("Data: {:?}", &data[..15]);

    // Print the last 15 elements of the data
    println!("Data: {:?}", &data[data.len()-15..]);
}