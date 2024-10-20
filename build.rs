// build.rs
fn main() {
    println!("cargo:rustc-link-lib=getdata"); // Link against the libgetdata library
    println!("cargo:rustc-link-search=/usr/lib"); // Ensure the library path is searched
    println!("cargo:include=/usr/include"); // Include the directory for headers
}
