#!/system/bin/sh
mainfunction() {
#cleanup
rm /data/local/tmp/sf 2>/dev/null


SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
abi=$(getprop ro.product.cpu.abi)

if [ "$abi" = "armeabi-v7a" ]; then
cp $SCRIPT_DIR/file/armv7a/sf /data/local/tmp/
elif [ "$abi" = "arm64-v8a" ]; then
cp $SCRIPT_DIR/file/armv8a/sf /data/local/tmp/
else 
echo "Your ABI is not armeabi-v7a or arm64-v8a , exit"
exit 1
fi

#chmod
chmod 777 /data/local/tmp/sf
/data/local/tmp/sf
}
mainfunction