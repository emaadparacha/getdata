// Case warnings
#![allow(non_upper_case_globals)]

// getdata Bindings
use super::getdata_bindings::*;
use std::ffi::CString;
use std::any::Any;

pub struct DirFile {
    pub dirfile_open: *mut DIRFILE,
}

// Enum to store the data of a field in a DirFile
pub enum FieldData {
    Uint8(Vec<u8>),
    Int8(Vec<i8>),
    Uint16(Vec<u16>),
    Int16(Vec<i16>),
    Uint32(Vec<u32>),
    Int32(Vec<i32>),
    Uint64(Vec<u64>),
    Int64(Vec<i64>),
    Float32(Vec<f32>),
    Float64(Vec<f64>),
    String(Vec<String>),
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

    // Function to get the data of a field in a DirFile
    pub fn get_data(&self, field: &str) -> Vec<FieldData> {
        let field_type = self.field_type(field);
        let nframes = self.nframes();
        let samples_per_frame = self.spf(field);
        let total_samples = nframes * (samples_per_frame as i64);

        // Bind the CString to a variable
        let field = CString::new(field).expect("CString::new failed");
        let field_code_ptr = field.as_ptr(); // Get the pointer to the CString

        match field_type {
            gd_type_t_GD_UINT8 => {
                let mut data = vec![0u8; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT8,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Uint8(data)]
            }
            gd_type_t_GD_INT8 => {
                let mut data = vec![0i8; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT8,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Int8(data)]
            }
            gd_type_t_GD_UINT16 => {
                let mut data = vec![0u16; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT16,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Uint16(data)]
            }
            gd_type_t_GD_INT16 => {
                let mut data = vec![0i16; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT16,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Int16(data)]
            }
            gd_type_t_GD_UINT32 => {
                let mut data = vec![0u32; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT32,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Uint32(data)]
            }
            gd_type_t_GD_INT32 => {
                let mut data = vec![0i32; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT32,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Int32(data)]
            }
            gd_type_t_GD_UINT64 => {
                let mut data = vec![0u64; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_UINT64,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Uint64(data)]
            }
            gd_type_t_GD_INT64 => {
                let mut data = vec![0i64; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_INT64,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Int64(data)]
            }
            gd_type_t_GD_FLOAT32 => {
                let mut data = vec![0.0f32; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_FLOAT32,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Float32(data)]
            }
            gd_type_t_GD_FLOAT64 => {
                let mut data = vec![0.0f64; total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_FLOAT64,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                vec![FieldData::Float64(data)]
            }
            gd_type_t_GD_STRING => {
                // Handle string data accordingly
                let mut data = vec![CString::new("").unwrap(); total_samples as usize];
                unsafe {
                    gd_getdata(
                        self.dirfile_open,
                        field_code_ptr,
                        0,
                        0,
                        nframes as usize,
                        samples_per_frame as usize,
                        gd_type_t_GD_STRING,
                        data.as_mut_ptr() as *mut ::std::os::raw::c_void,
                    );
                }
                let data: Vec<String> = data.into_iter()
                    .map(|c| c.into_string().unwrap())
                    .collect();
                vec![FieldData::String(data)]
            }
            _ => Vec::new(), // Handle unknown types
        }
    }

}