const {
  wasi_clock_res_get,
  wasi_time_get,
} = Deno.dlopen(
  new URL("../wasi.so", import.meta.url),
  {
    wasi_clock_res_get: {
      parameters: ["u32", "buffer"],
      result: "u32",
    },

    wasi_time_get: {
      parameters: ["u32", "buffer"],
      result: "u32",
    },
  },
).symbols;

export function instanciateWasi(
  bytes: Uint8Array,
  imports: WebAssembly.Imports = {},
): WebAssembly.WebAssemblyInstantiatedSource {
  const module = new WebAssembly.Module(bytes);
  const instance = new WebAssembly.Instance(module, {
    wasi_snapshot_preview1: {
      clock_get_res: (clockId: number, offset: number) => {
        return wasi_clock_res_get(clockId, new Uint8Array((instance.exports.memory as WebAssembly.Memory).buffer, offset, 8));
      },
      clock_time_get: (clockId: number, _precision: bigint, offset: number) => {
        return wasi_time_get(clockId, new Uint8Array((instance.exports.memory as WebAssembly.Memory).buffer, offset, 8));
      },
    },
    ...imports,
  });

  return {
    module,
    instance,
  };
}
