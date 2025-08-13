#!/bin/sh

BASE_DIR="$(pwd)"
SRC_DIR="$BASE_DIR/hd_bitbucket"
TARGET_DIR="$BASE_DIR/ap_app"

modules="adaptive_autosar ap_sm ap_soa ap_soa_debugger ap_soa_dms ap_soa_driverseat ap_soa_hvac ap_soa_moodlamp ap_soa_power ap_soa_rearcurtain ap_soa_roa ap_soa_smartfilm ap_soa_wiper ap_subscriptionmanager ap_ipchandler"

mkdir -p "$TARGET_DIR"

echo "📦 Updating Bitbucket modules..."

for module in $modules; do
    echo "🔄 Pulling $module ..."
    if [ -d "$SRC_DIR/$module/.git" ]; then
        git -C "$SRC_DIR/$module" pull || {
            echo "❌ Failed to pull $module"
            continue
        }
    else
        echo "⚠️ No git repo found for $module in $SRC_DIR, skipping..."
        continue
    fi

    echo "📂 Copying $module to $TARGET_DIR/$module ..."
    mkdir -p "$TARGET_DIR/$module"
    rsync -a --exclude='.git' "$SRC_DIR/$module/" "$TARGET_DIR/$module/"
    rm -rf "$TARGET_DIR/$module/.git"
done

echo "✅ All modules updated (including adaptive_autosar)"

echo "🔗 Creating adaptive_autosar symlinks in app modules..."

for module in $modules; do
    if [ "$module" = "adaptive_autosar" ]; then
        # adaptive_autosar는 심볼릭 링크 생성 안 함
        continue
    fi

    LINK_DIR="$TARGET_DIR/$module"
    if [ -d "$LINK_DIR" ]; then
        echo "🔗 Creating symlink in $LINK_DIR"
        rm -rf "$LINK_DIR/adaptive_autosar"
        ln -s ../../adaptive_autosar "$LINK_DIR/adaptive_autosar"
    else
        echo "⚠️ Directory $LINK_DIR not found, skipping symlink creation"
    fi
done

echo "✅ Symlinks updated."

