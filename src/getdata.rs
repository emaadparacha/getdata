// Case warnings
#![allow(non_upper_case_globals)]

// getdata Bindings
use super::getdata_bindings::*;
use std::ffi::CString;

pub struct DirFile {
    pub dirfile_open: *mut DIRFILE,
}

impl DirFile {

    // Function to create a new DirFile instance from a path
    pub fn new(path: &str) -> Self {
        let dirfile = CString::new(path).expect("CString::new failed");
        let dirfile_ptr = dirfile.as_ptr();
        let dirfile_open = unsafe { gd_open(dirfile_ptr, GD_RDONLY) };
        Self {
            dirfile_open,
        }
    }

    // Function to get the number of fields in the DirFile
    pub fn nfields(&self) -> u32 {
        unsafe { gd_nfields(self.dirfile_open) }
    }

    // Function to get the total number of frames in a DirFile
    pub fn nframes(&self) -> i64 {
        unsafe { gd_nframes(self.dirfile_open) }
    }

    // Function to get the samples per frame for a field in a DirFile
    pub fn spf(&self, field: &str) -> u32 {
        let field_code = CString::new(field).expect("CString::new failed");
        let field_code_ptr = field_code.as_ptr();
        unsafe { gd_spf(self.dirfile_open, field_code_ptr) }
    }

    // Function to get the type of a field in a DirFile
    pub fn field_type(&self, field: &str) -> u32 {
        let field_code = CString::new(field).expect("CString::new failed");
        let field_code_ptr = field_code.as_ptr();
        unsafe { gd_native_type(self.dirfile_open, field_code_ptr) }
    }


    // Function to get the data of a field in a DirFile and return as Vec<f64>
    pub fn get_data(&self, field: &str) -> Vec<f64> {
        let field_type = self.field_type(field);
        let nframes = self.nframes();
        let samples_per_frame = self.spf(field);
        let total_samples = nframes * (samples_per_frame as i64);

        let field_code = CString::new(field).expect("CString::new failed");
        let field_code_ptr = field_code.as_ptr(); // Get the pointer to the CString

        let data = match field_type {
            gd_type_t_GD_UINT8 => {
                let mut raw_data = vec![0u8; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT8,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.iter().map(|&v| v as f64).collect()
            }
            gd_type_t_GD_INT8 => {
                let mut raw_data = vec![0i8; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT8,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.iter().map(|&v| v as f64).collect()
            }
            gd_type_t_GD_UINT16 => {
                let mut raw_data = vec![0u16; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT16,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.iter().map(|&v| v as f64).collect()
            }
            gd_type_t_GD_INT16 => {
                let mut raw_data = vec![0i16; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT16,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.iter().map(|&v| v as f64).collect()
            }
            gd_type_t_GD_UINT32 => {
                let mut raw_data = vec![0u32; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT32,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.iter().map(|&v| v as f64).collect()
            }
            gd_type_t_GD_INT32 => {
                let mut raw_data = vec![0i32; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT32,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.iter().map(|&v| v as f64).collect()
            }
            gd_type_t_GD_UINT64 => {
                let mut raw_data = vec![0u64; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT64,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.iter().map(|&v| v as f64).collect()
            }
            gd_type_t_GD_INT64 => {
                let mut raw_data = vec![0i64; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT64,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.iter().map(|&v| v as f64).collect()
            }
            gd_type_t_GD_FLOAT32 => {
                let mut raw_data = vec![0.0f32; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_FLOAT32,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.iter().map(|&v| v as f64).collect()
            }
            gd_type_t_GD_FLOAT64 => {
                let mut raw_data = vec![0.0f64; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_FLOAT64,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data // Already a Vec<f64>
            }
            gd_type_t_GD_STRING => {
                // Handle string data accordingly
                let mut raw_data = vec![CString::new("").unwrap(); total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_STRING,
                        raw_data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                raw_data.into_iter()
                    .filter_map(|c| c.into_string().ok())
                    .map(|s| s.parse::<f64>().unwrap_or(0.0)) // Example conversion
                    .collect()
            }
            _ => {
                // Handle unknown types or return an empty vector
                println!("Unknown field type: {}", field_type);
                Vec::new()
            }
        };

        data // Return the processed data
    }

}